clc
clear all
close all

onWindows = true;

% Set home path
curDir = pwd;
if onWindows
	dataPath = 'C:\Users\carson\Desktop\libs\data\';
	lftbPath = 'C:\Users\carson\Desktop\raytrix_api_tests\functions_test\lf_toolbox\LFToolbox0.4\';
	lensInfoPath = 'C:\Users\carson\Desktop\libs\data\mxa_details.txt';
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

lensInfo = importdata(lensInfoPath);

% Load the gray image
graySrc = imread(strcat(dataPath, 'gray.png'));
% Load main raw image
src = imread(strcat(dataPath, 'processed.png'));