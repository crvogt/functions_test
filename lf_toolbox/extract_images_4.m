clc
close all;
clear all;

onWindows = false;

if onWindows
	imgPath = 'C:\Users\carson\Desktop\libs\data\processed.png';
	dataPath = 'C:\Users\carson\Desktop\libs\data\mxa_details.txt';
else 
	imgPath = 'processed.png';
	dataPath = 'mxa_details.txt';
end

%Load image
[img, daMap] = imread(imgPath, 'png');

A = importdata(dataPath);
lens0 = A(1:2929,1:2);
lens1 = A(2930:5858, 1:2);
lens2 = A(5859:8760, 1:2);

yMax = max(lens2(:,1));
yThresh = 0.16;
iter = 1;
while iter < length(lens2)
	if(lens2(iter,1) >= (yMax - yThresh))
		lens2(iter,:) = [];
	end
	iter = iter + 1;
end

% Put the lenses into a lftoolbox-friendly structure

LF = zeros(25, 25, 101, 87, 3);

% Get an individual lens. Effective radius ~11.5, so call it 12.
effR = 12;
SVec = -6:6;
TVec = -6:6;
UVec = 1:101;
VVec = 1:87;

[tt,ss,vv,uu] = ndgrid(TVec, SVec, VVec, UVec);
R = sqrt(tt.^2 + ss.^2);

numLenses = 29;
lensImg = zeros(effR*2+1, effR*2+1, 3);
count0 = 1;
count1 = 1;
count2 = 1;
track = 1;
trackPrev = 0;
Ucount = 87;
UStart = Ucount;
Vcount = 101;
for counter = 1:(length(lens0)+length(lens1)+length(lens2))
	
	switch track
		case(1)
			if (ceil(lens1(count0,2)) - lens1(count1,2)) >= 0.5
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

		case(2)
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

		case(0)
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
	
	for it = 1:effR*2+1
		for jt = 1:effR*2+1
			dist = sqrt((jt-(effR+1))^2 + (it-(effR+1))^2);
			if dist > 12.5
				lensImg(it,jt,:) = 0;
			end
		end
	end

	% LF(:,:,Vcount, Ucount,:)
	% lensImg = double(lensImg);
	LF(:,:,Vcount, Ucount,:) = lensImg;

	Ucount = Ucount - 1;
	if Ucount == 0
		if UStart == 87
			Ucount = 86;
			UStart = Ucount;
		elseif UStart == 86
			Ucount = 87;	
			UStart = Ucount;		
		end
		Vcount = Vcount - 1;
		track = trackPrev;
	end
end

size(LF)
LFLens = squeeze(LF(:,:,round(end/2),round(end/2),:));
size(LFLens)
figure()
imshow(LFLens)

for iter = 1:size(LF,3)
	for jter = 1:size(LF,4)

        if jter == 1
            basicImg = LF(:,:,iter,jter,:);
            basicImg = squeeze(uint16(basicImg));
        else 
            lensImg = LF(:,:,iter,jter,:);
            lensImg = squeeze(uint16(lensImg));
            basicImg = cat(2, basicImg, lensImg);
        end 
    end
    if iter == 1
        fullImg = basicImg;
    else
        fullImg = cat(1,fullImg,basicImg);
    end      
end 

figure()
imshow(fullImg)
