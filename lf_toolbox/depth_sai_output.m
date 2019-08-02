clc
clear all
close all

%imgPath = 'l5_s5_g25.png';
% imgPath = '/home/carson/libs/raytrix_data/light_test_1/l1/g0/l1_s5_g0_0000041617_Processed.png';
% writePath = '/home/carson/libs/raytrix_data/light_test_1/l1/g0/l1g0sai';

imgPath = '/home/carson/libs/store_imgs/dist_foc_tests/proc.png'
writePath = '/home/carson/libs/store_imgs/dist_foc_tests/sais'

LF = get_sub_ap(imgPath);

LFWriteOutDepthSAI_crv(LF, writePath);

fprintf('\nfin\n');
