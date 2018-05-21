clc
clear all
close all

imgNum = 100;
channels = 3;
numRows = 10;
numCols = 10;

fullStruct = zeros(numRows, numCols, channels, imgNum, imgNum);

sliceIm = fullStruct(:,:,:,1,1);

size(sliceIm)

% sliceIm(y, x, chan)
sliceIm(1:3, 1:5, 1) = 255;
sliceIm(1:3, 1:5, 2) = 0;
sliceIm(1:3, 1:5, 3) = 0;
figure(1)
image(sliceIm)

slice2 = sliceIm;
slice2(1:3, 1:5, 1) = 0;
slice2(1:3, 1:5, 2) = 255;
slice3 = sliceIm;

mainFig = cat(2, sliceIm, slice2);
mainFig = cat(2, mainFig, slice3);
image(mainFig)
% figure(2)
% montage(repmat(sliceIm,[1 1 1 4]));

for iter = 1:imgNum
	for jter = 1:imgNum
		% iter
		% jter
		fullStruct(1:3, 1:5, :, iter, jter) = 255;
		if jter == imgNum && iter == imgNum
			fullStruct(1:3, 1:5, 1, iter, jter) = 100;
			fullStruct(1:3, 1:5, 2, iter, jter) = 0;
			fullStruct(1:3, 1:5, 3, iter, jter) = 0;
		end

	end
end

% figure(3)
% bleh = montage(fullStruct, 'DisplayRange', [1 1000])
% size(fullStruct)


