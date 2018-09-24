clc
clear all

pathToData = '/home/carson/libs/raytrix_data/light_test_1/psnrData.txt';
A = importdata(pathToData);
T = readtable(pathToData);

% h = heatmap(A(1:20,4), A(1:20,2), A(1:20,3));
% surf(A(1:20,2), A(1:20,3), A(1:20,4))