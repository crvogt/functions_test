clc
clear all
close all

imgNum = 100;
channels = 3;
numRows = 10;
numCols = 10;

fullStruct = zeros(numRows, numCols, channels, imgNum, imgNum);

% for iter = 1:imgNum
% 	for jter = 1:imgNum
% 		fullStruct(1:3, 1:5, :, iter, jter) = 255;
% 		if jter == imgNum && iter == imgNum
% 			fullStruct(1:3, 1:5, 1, iter, jter) = 100;
% 			fullStruct(1:3, 1:5, 2, iter, jter) = 0;
% 			fullStruct(1:3, 1:5, 3, iter, jter) = 0;
% 		elseif iter == imgNum && jter == 1
% 			fullStruct(1:3, 1:5, 1, iter, jter) = 100;
% 			fullStruct(1:3, 1:5, 2, iter, jter) = 0;
% 			fullStruct(1:3, 1:5, 3, iter, jter) = 200;
% 		end

% 	end
% end

fullStruct(:,:,3, 90:100, 90:100) = 255;

for iter = 1:imgNum
	for jter = 1:imgNum
		if jter == 1
			slice = fullStruct(:,:,:, jter, iter);
		else 
			slice = cat(1,slice, fullStruct(:,:,:, jter, iter));
		end
	end
	if iter == 1
		fprintf('\nJust once\n');
		panel = slice;
	else
		panel = cat(2, panel, slice);
	end
end

figure(1)
image(panel);