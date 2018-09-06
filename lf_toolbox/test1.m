clc
clear all
close all

% Set home path
% dataPath = 'C:\Users\carson\Desktop\libs\data\';
dataPath = '/home/carson/functions_test/raytrix_tests/data/';

% Set paths for lf toolbox
curDir = pwd;
% lftbPath = 'C:\Users\carson\Desktop\libs\LFToolbox0.4\';
lftbPath = '/home/carson/functions_test/lf_toolbox/LFToolbox0.4/';
cd(lftbPath);
LFMatlabPathSetup();
cd(curDir);
fprintf('Path set...\n');

% Load the gray image
graySrc = imread(strcat(dataPath, 'gray.png'));
% Load main raw image
src = imread(strcat(dataPath, 'processed.png'));
fprintf('Images loaded...\n');

[LF, DecodeOptions] = LFDecodeLensletImageSimple_crv(src);

size(LF)
% size(CorrectedLensletImage)
% figure()
[lfToShow, imgOut] = LFDisp(LF);
size(imgOut)
tmpImg = LF(1,1,:,:,:);
size(tmpImg)
tmpImg = squeeze(tmpImg);
size(tmpImg)
figure()
imshow(uint16(tmpImg))
figure()
imshow(imgOut)
% imshow(imgOut)
% figure()
% imshow(CorrectedLensletImage)
% figure()
% tmpImg = 
% imshow(LF(1,1,:,:,:))