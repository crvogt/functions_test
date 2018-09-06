clc
clear all

% Set home path
% dataPath = 'C:\Users\carson\Desktop\libs\data\';
dataPath = 'Images/Illum/Jacaranda.lfp';

% Set paths for lf toolbox
curDir = pwd;
% lftbPath = 'C:\Users\carson\Desktop\libs\LFToolbox0.4\';
lftbPath = '/home/carson/functions_test/lf_toolbox/LFToolbox0.4/';
cd(lftbPath);
LFMatlabPathSetup();
cd(curDir);
fprintf('Path set...\n');
cd('/home/carson/libs/LFToolbox0.3_Samples1');

[LF, ~, ~, ~, CorrectedLensletImage] = LFLytroDecodeImage(dataPath);

size(LF)
size(CorrectedLensletImage)

cd(curDir);

LFDisp(LF)