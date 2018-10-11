clc
clear all
close all

img = imread('40.jpg');

[height, width, ~] = size(img);

[X, Y] = meshgrid(1:width, 1:height);

grayImg = single(rgb2gray(img));

curDepth = -10;
curY = Y + curDepth * 1;
curX = X + curDepth * 1;

size(grayImg)
newView = interp2(X, Y, grayImg, curX, curY, 'cubic', nan);
size(newView)

imshow(uint8(newView));
imwrite(uint8(newView),'matlab_version.jpg');