clc
clear all
close all

deltaDisparity = 21;
depthResolution = 100; %Number of depth channels

LF = get_sub_ap();
subApGrid = LFReturnGrid_crv(LF);
[height, width, ~, angHeight, angWidth] = size(subApGrid);
LFWriteOutGridDenoise_crv(LF)