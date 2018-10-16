clc
clear all
close all

imgPath = 'l5_s5_g25.png';

LF = get_sub_ap(imgPath);

LFWriteOutDepthSAI_crv(LF);