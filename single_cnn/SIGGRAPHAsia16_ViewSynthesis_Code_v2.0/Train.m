clearvars; clearvars -global; clc; close all;

addpath('Functions');
addpath(genpath('./Libraries'));

vl_setupnn();
fprintf('\nFirst\n');
InitParam();

fprintf('\nFirst\n');

PrepareTrainingData();
% PrepareTestData();
pause(20);

[depthNet, colorNet] = LoadNetworks(true);

TrainSystem(depthNet, colorNet);