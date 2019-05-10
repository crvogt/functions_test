function LF = get_sub_ap_03(imgPath)
    imgPath = imgPath; % {1};
    % clc
    % close all
    % clear all
    % imgPath = '/home/carson/libs/gray_to_png/0034035116/plant_processed.png'

	onWindows = false;

	if onWindows
		imgPath = 'C:\Users\carson\Desktop\libs\data\processed.png';
		dataPath = 'C:\Users\carson\Desktop\libs\data\mxa_details.txt';
	else 
		% cd('/home/carson/LFToolbox0.4');
		addpath('/home/carson/functions_test/lf_toolbox/LFToolbox0.4/')
		LFMatlabPathSetup();
		
		fprintf('\nOpening %s...\n', imgPath);
		dataPath = '/home/carson/libs/gray_to_png/0034035116/mxa_details.txt';
	end

	%Load image
    [img, ~] = imread(imgPath);
    % img = demosaic(img, 'gbrg');

	A = importdata(dataPath);
	lens0 = A(1:2900,1:2);
	lens1 = A(2901:5800, 1:2);
	lens2 = A(5801:8700, 1:2);

	% figure(1)
	% imshow(img)
	% hold on;
	% plot(lens0(:, 1), lens0(:, 2), '.', 'MarkerSize', 20)
	% plot(lens1(:, 1), lens1(:, 2), '.k')
	% plot(lens2(:, 1), lens2(:, 2), '.g')
	% hold off;

	% pause(100)

	% Get an individual lens. Effective radius ~10.5, so call it 11.
	effR = 11;
	SVec = -6:6;
	TVec = -6:6;
	UVec = 1:101;
	VVec = 1:87;

	% Put the lenses into a lftoolbox-friendly structure

	LF = zeros(effR*2+1, effR*2+1, 101, 87, 3);

	[tt,ss,vv,uu] = ndgrid(TVec, SVec, VVec, UVec);
	R = sqrt(tt.^2 + ss.^2);

	numLenses = 29;
	lensImg = zeros(effR*2+1, effR*2+1, 3);
	count0 = 1;
	count1 = 1;
	count2 = 1;
	track = 0;
	trackPrev = 0;
	Ucount = 87;
	UStart = Ucount;
	Vcount = 101;
	% length(lens2)
	% pause(20)
	for counter = 1:(length(lens0)+length(lens1)+length(lens2))
		% count0 + count1 + count2
		% track
		% fprintf('count1 %d, count2 %d, count0 %d, track %d\n', count1, count2, count0, track)
		switch track
			case(1) %1
				if (ceil(lens1(count1,2)) - lens1(count1,2)) >= 0.5
					rowVal = floor(lens1(count1,2));
				else 
					rowVal = ceil(lens1(count1,2));
				end
				if (ceil(lens1(count1,1)) - lens1(count1,1)) >= 0.5
					colVal = floor(lens1(count1,1));
				else 
					colVal = ceil(lens1(count1,1));
				end
				count1 = count1 + 1;
				trackPrev = track;
				track = track+1;

			case(2) %2
				if (ceil(lens2(count2,2)) - lens0(count2,2)) >= 0.5
					rowVal = floor(lens2(count2,2));
				else 
					rowVal = ceil(lens2(count2,2));
				end
				if (ceil(lens2(count2,1)) - lens2(count2,1)) >= 0.5
					colVal = floor(lens2(count2,1));
				else 
					colVal = ceil(lens2(count2,1));
				end
				count2 = count2 + 1;
				trackPrev = track;
				track = 0;

			case(0) %0
				if (ceil(lens0(count0,2)) - lens0(count0,2)) >= 0.5
					rowVal = floor(lens0(count0,2));
				else 
					rowVal = ceil(lens0(count0,2));
				end
				if (ceil(lens0(count0,1)) - lens0(count0,1)) >= 0.5
					colVal = floor(lens0(count0,1));
				else 
					colVal = ceil(lens0(count0,1));
				end
				count0 = count0 + 1;
				trackPrev = track;
				track = track+1;
		end

		lensImg = imcrop(img,[colVal-effR, rowVal-effR, effR*2, effR*2]);
		% close all
		% delete p_temp;
		

		% figure(1)
		% imshow(img)
		% hold on;
		% plot(lens0(:, 1), lens0(:, 2), '*r', 'MarkerSize', 5)
		% plot(lens1(:, 1), lens1(:, 2), '.k', 'MarkerSize', 10)
		% plot(lens2(:, 1), lens2(:, 2), '.g', 'MarkerSize', 10)
		% p_temp = plot((colVal), (rowVal), '*m', 'MarkerSize', 30);
		% hold off;
		

		for it = 1:effR*2+1
			for jt = 1:effR*2+1
				dist = sqrt((jt-(effR+1))^2 + (it-(effR+1))^2);
				if dist > (effR+1)
					lensImg(it,jt,:) = 0;
				end
			end
		end
		% size(LF)
		% size(lensImg)
		LF(:,:,Vcount, Ucount,:) = lensImg;
		% fprintf('track: %d', trackPrev);
		% figure(2)
		% hold on;
		% imshow(lensImg)
		% hold off;
		% pause(1)
		Ucount = Ucount - 1;
		if Ucount == 0
			if UStart == 87
				Ucount = 87;
				UStart = Ucount;
			elseif UStart == 87
				Ucount = 87;	
				UStart = Ucount;		
			end
			% imgslice = squeeze(LF(1, 1, :, :, :));
			% size(imgslice)
			% imshow(imgslice)
			% pause(4)
			Vcount = Vcount - 1;
			% temp = track;
			% if trackPrev == 2
			% 	track = 1;
			% elseif trackPrev == 0
			% 	track = 2;
			% elseif trackPrev == 2
				% track = 0
			% end
			% track = trackPrev;
			% trackPrev = temp;
			if trackPrev == 2
				track = 1;
			elseif trackPrev == 0
				track = 0;
			end
		end
		% pause(.2)
	end

	LF = flip(LF, 4);

	for iter = 1:size(LF,3)
		for jter = 1:size(LF,4)

	        if jter == 1
	            basicImg = LF(:,:,iter,jter,:);
	            basicImg = squeeze(uint8(basicImg));
	        else 
	            lensImg = LF(:,:,iter,jter,:);
	            lensImg = squeeze(uint8(lensImg));
	            basicImg = cat(2, basicImg, lensImg);
	        end 
	    end
	    if iter == 1
	        fullImg = basicImg;
	    else
	        fullImg = cat(1,fullImg,basicImg);
	    end      
	end 

	close all

	fprintf('\nDehexing\n');

	LF = LFDehex_crv(LF);
    LFDisp_crv(LF);


end