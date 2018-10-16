clc
clear all
close all

imgPath1 = 'l5_s5_g25.png';
imgPath2 = 'l1_s5_g100.png';

LFBright = get_sub_ap(imgPath1);
LFDim = get_sub_ap(imgPath2);

LFWriteOutGridDenoise_crv(LFBright, LFDim, true)