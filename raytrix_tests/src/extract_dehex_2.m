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
hold off;

figure()
hold on;
plot(lens0(:,1), -lens0(:,2), 'or', 'MarkerSize', 10);
plot(lens1(:,1), -lens1(:,2), '.k', 'MarkerSize', 10);
plot(lens2(:,1), -lens2(:,2), 'db', 'MarkerSize', 10);
hold off;

% Get an individual lens. Effective radius ~11.5, so call it 12.
effR = 12;
numLenses = 29;
lensImg = zeros(effR*2+1, effR*2+1, 3);
chosenLenses = zeros(effR*2+1, effR*2+1, 3, numLenses, 'uint16');
for counter = 1:1:numLenses

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
	lensImg = imcrop(img,[colVal-effR, rowVal-effR, effR*2, effR*2]);
	
	chosenLenses = lensImg; 
end

figure()
montage(chosenLenses, 'Size', [1 numLenses])
