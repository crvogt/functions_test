clc
clear all
close all

onWindows = true;

% Set home path
curDir = pwd;
if onWindows
	dataPath = 'C:\Users\carson\Desktop\libs\data\';
	lftbPath = 'C:\Users\carson\Desktop\raytrix_api_tests\functions_test\lf_toolbox\LFToolbox0.4\';
	cd(lftbPath);
	LFMatlabPathSetup();
	cd(curDir);
	fprintf('Path set...\n');
else 
	dataPath = '/home/carson/functions_test/raytrix_tests/data/';
	lftbPath = '/home/carson/functions_test/lf_toolbox/LFToolbox0.4/';
	cd(lftbPath);
	LFMatlabPathSetup();
	cd(curDir);
	fprintf('Path set...\n');
end


% Load the gray image
graySrc = imread(strcat(dataPath, 'gray.png'));
% Load main raw image
src = imread(strcat(dataPath, 'processed.png'));
fprintf('Images loaded...\n');

[LF, DecodeOptions] = LFDecodeLensletImageSimple_crv(src);

size(LF)
% size(CorrectedLensletImage)
% figure()
[lfToShow, imgOut] = LFDisp_crv(LF);
size(imgOut)
% tmpImg = LF(1,1,:,:,:);
% size(tmpImg)
% tmpImg = squeeze(tmpImg);
% size(tmpImg)
% figure()
% imshow(uint16(tmpImg))
% figure()
% imshow(imgOut)

% figure()
% LFImg = LF(round(end/2),:,:,:,:);
% LFImg = squeeze(LFImg)
% imshow(LFImg)
% imshow(imgOut)
% figure()
% imshow(CorrectedLensletImage)
% figure()
% tmpImg = 
% imshow(LF(1,1,:,:,:))