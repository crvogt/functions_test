clc
close all;
clear all;

onWindows = true;

if onWindows
	imgPath = 'C:\Users\carson\Desktop\libs\data\processed.png';
	dataPath = 'C:\Users\carson\Desktop\libs\data\mxa_details.txt';
end

%Load image
[img, daMap] = imread(imgPath, 'png');
figure()

% if isempty(daMap)
% 	warndlg('Map is empty...');
% else
% 	helpdlg('Map not empty!');
% end

imshow(img, daMap)
% img
%Load data
A = importdata(dataPath);
lens0 = A(1:2929,1:2);
lens1 = A(2930:5858, 1:2);
lens2 = A(5859:8760, 1:2);

% length(lens2)
% for iter = 1:length(A)
yMax = max(lens2(:,1));
yThresh = 0.16;
iter = 1;
while iter < length(lens2)
	if(lens2(iter,1) >= (yMax - yThresh))
		lens2(iter,:) = [];
	end
	iter = iter + 1
end
% end

% pause(100)

figure()
hold on;
plot(lens0(:,1), -lens0(:,2), 'or', 'MarkerSize', 10);
plot(lens1(:,1), -lens1(:,2), '.k', 'MarkerSize', 10);
plot(lens2(:,1), -lens2(:,2), 'db', 'MarkerSize', 10);
hold off;

% pause(100)

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

upDown = -11;
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



