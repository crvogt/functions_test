clc
clear all

% Set home path
dataPath = 'C:\Users\carson\Desktop\libs\data\';

% Set paths for lf toolbox
curDir = pwd;
lftbPath = 'C:\Users\carson\Desktop\libs\LFToolbox0.4\';
cd(lftbPath);
LFMatlabPathSetup();
cd(curDir);
fprintf('Path set...\n');

% Load the gray image
graySrc = imread(strcat(dataPath, 'gray.png'));
% Load main raw image
src = imread(strcat(dataPath, 's_10_Raw.png'));
fprintf('Images loaded...\n');
