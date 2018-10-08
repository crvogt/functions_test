% Need to minimize the function:
% For all the view points
% E = sum_u ||L0 - L0_shift||^2

% Get depth in similar way to view synth

% Down sample an image

% Get skip connection working

clc
clear all
close all

deltaDisparity = 21;
depthResolution = 100; %Number of depth channels

LF = get_sub_ap();
subApGrid = LFReturnGrid_crv(LF);
[height, width, ~, angHeight, angWidth] = size(subApGrid);

for i = 1:angHeight
	for j = 1:angWidth 
		grayLF(:,:,i,j) = rgb2gray(uint16(subApGrid(:,:,:,i,j)));
	end
end

defocusStack = zeros(height, width, depthResolution);
correspStack = zeros(height, width, depthResolution);
featuresStack = zeros(height, width, depthResolution*2, 'single');

delta = 2*deltaDisparity/(depthResolution-1);

for curDepth = -deltaDisparity:delta:deltaDisparity
	shearedLF = zeros(height, width, angHeight*angWidth);


end
