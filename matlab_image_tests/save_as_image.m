clc
clear all
close all

im = imread('0.jpg');

% Save this as theta1 phi1 theta2 phi2
locMat = zeros(480, 640, 4);

saveTo = '/media/carson/WDPassport/deep_learn/pr2_dataset/set_1/parameterization/';
poseLoc = int2str(it);
saveTo = strcat(saveTo, poseLoc);
saveTo = strcat(saveTo, '.mat');
save(saveTo, 'pointList');

