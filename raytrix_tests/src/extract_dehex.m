clc
close all;
clear all;

%Load image
[img, daMap] = imread('../data/processed.png', 'png');

A = importdata('../data/mxa_details.txt');
lens0 = A(1:2929,1:2);
lens1 = A(2930:5858, 1:2);
lens2 = A(5859:8760, 1:2);

figure()
imshow(img, daMap)

hold on;
plot(lens0(1,1), lens0(1,2), '*r', 'MarkerSize', 20);
plot(lens0(:,1), lens0(:,2), '.r', 'MarkerSize', 5);
plot(lens1(:,1), lens1(:,2), '.r', 'MarkerSize', 5);
plot(lens2(:,1), lens2(:,2), '.r', 'MarkerSize', 5);
% plot(x,y,'r.', 'MarkerSize', 5);
hold off;

% test = imcrop(img, [0 0 200 200]);
% imshow(test)

% pause(1000)

figure()
hold on;
plot(lens0(:,1), -lens0(:,2), 'or', 'MarkerSize', 10);
plot(lens1(:,1), -lens1(:,2), '.k', 'MarkerSize', 10);
plot(lens2(:,1), -lens2(:,2), 'db', 'MarkerSize', 10);
hold off;

rowStep = 2;
if rowStep > 1
	rowCount = 51 * rowStep - 1;
else
	rowCount = 51;
end

colStep = 6;
colCount = 29*colStep;

accImage = zeros(rowCount, colCount,3,'uint16');
accImage = accImage + 70000;

upDown = 0;
leftRight = 0; 

%%%%%%%%%%%%%Lens1%%%%%%%%%%%%%
counter = 1;
midPt = false;
for iRow = rowCount:-1:1
	for iCol = 1:6:colCount
		if midPt == true
			accImage(iRow,iCol+3,:) = img(floor(lens1(counter,2)) + upDown,floor(lens1(counter,1)) + leftRight,:);			
			counter = counter + 1;
		else
			accImage(iRow,iCol,:) = img(floor(lens1(counter,2)) + upDown,floor(lens1(counter,1)) + leftRight,:);
			counter = counter + 1;
		end
	end
	if midPt == false
		midPt = true;
	else 
		midPt = false;
	end
end

% %%%%%%%%%%%%%%Lens0%%%%%%%%%%%%%%%%
counter = 1;
midPt = false;
for iRow = rowCount:-1:1
		if midPt == true
			for iCol = 2:6:colCount
				accImage(iRow,iCol,:) = img(floor(lens0(counter,2)) + upDown,floor(lens0(counter,1)) + leftRight,:);
				counter = counter + 1;
			end
		else
			for iCol = 5:6:colCount
				accImage(iRow,iCol,:) = img(floor(lens0(counter,2)) + upDown,floor(lens0(counter,1)) + leftRight,:);
				counter = counter + 1;
			end
		end
	if midPt == false
		midPt = true;
	else 
		midPt = false;
	end
end
%%%%%%%%%%%%%Lens2%%%%%%%%%%%%%%%%%
% Starting from the bottom, midpoint rows only have 28;
counter = 1;
midPt = false;
for iRow = rowCount:-1:1
		if midPt == true
			for iCol = 6:6:colCount
				if(iCol == colCount && iRow > 46)

				else
					accImage(iRow,iCol,:) = img(floor(lens2(counter,2)) + upDown, floor(lens2(counter,1) + leftRight),:);
					counter = counter + 1;
				end
			end
		else
			for iCol = 3:6:colCount
				accImage(iRow,iCol,:) = (img(floor(lens2(counter,2)) + upDown, floor(lens2(counter,1) + leftRight),:));
				counter = counter + 1;
			end
		end
	if midPt == false
		midPt = true;
	else 
		midPt = false;
	end
end

figure()
imshow(accImage);

% Get an individual lens. Effective radius ~11.5, so call it 12.
effR = 12*1;
numLenses = 29;
lensImg = zeros(effR*2+1, effR*2+1, 3);
chosenLenses = zeros(effR*2+1, effR*2+1, 3, numLenses, 'uint16');
for counter = 30:1:30+numLenses
	% counter=1
	% counter
	if (ceil(lens0(counter,2)) - lens0(counter,2)) >= 0.5
		rowVal = floor(lens0(counter,2));
	else 
		rowVal = ceil(lens0(counter,2));
	end
	if (ceil(lens0(counter,1)) - lens0(counter,1)) >= 0.5
		colVal = floor(lens0(counter,1));
	else 
		colVal = ceil(lens0(counter,1));
	end

	% rowVal = 0;
	% lens0(1,1)
	% lens0(1,2)
	% colVal
	% rowVal
	% [rowVal-effR, colVal-effR, effR*2, effR*2]
	% lensImg = imcrop(img,[rowVal-effR, colVal-effR, effR*2+100, effR*2+1]);
	% testerImg = imcrop(img,[rowVal-effR, colVal-effR, effR*2, effR*2+500]);
	lensImg = imcrop(img,[colVal-effR, rowVal-effR, effR*2, effR*2]);
	chosenLenses(:,:,:,counter) = lensImg; 
	if counter == 1
		firstImg = lensImg;
		% chosenLenses = lensImg;
		% imshow(chosenLenses)
		% pause(10)
	else
	% 	chosenLenses = cat(3,lensImg);
	end
	
	% imshow(lensImg);
	% hold on;
	% plot(effR+1, effR+1, '.r', 'MarkerSize', 5);
	% hold off
	% pause(2)
	% close all;
end
% figure()
% imshow(chosenLenses(:,:,:,1));
% figure()
% imshow(firstImg)
% firstImg(1,1,1)
% chosenLenses(1,1,1,1)
figure()
% montage(chosenLenses, 'Size', [1 numLenses])
% size(chosenLenses)
montage(chosenLenses, 'Size', [1 numLenses])


% for counter = 1:100:2000
% 	% counter = 1000;

% 	for iRow = -12:1:12
% 		for iCol = -12:1:12
% 			lensImg(iRow+13,iCol+13,:) = img(floor(lens0(counter,2))+iRow+upDown,floor(lens0(counter,1))+iCol+leftRight,:);
% 		end
% 	end

% 	figure()
% 	imshow(lensImg);
% 	pause(1)
% 	close all
% end