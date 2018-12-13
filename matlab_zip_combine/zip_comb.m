clc
clear all
close all

base_dir = '/home/carson/libs/raytrix_gp_data/raytrixImages/low_light_proc/devignette';

dark_read = strcat(base_dir, '/10.png');
light_read = strcat(base_dir, '_enhance/10.png');
dark_read2 = '/home/carson/libs/raytrix_gp_data/raytrixImages/imgs_to_enhance/total_focus/dark/10.png';
light_read2 = '/home/carson/libs/raytrix_gp_data/raytrixImages/imgs_to_enhance/total_focus/enh/10.png';


dark_src = imread(dark_read);
dark_src2 = imread(dark_read2);
light_src = imread(light_read);
light_src2 = imread(light_read2);

% light_src = light_src(:, 1025:2048, :);
% imshow(light_src);
% pause(20)
% 
dark_src(:, 1:1025, :) = light_src(:, 1:1025, :);
dark_src2(:, 1:512, :) = light_src2(:, 1:512, :);
% 
imshow(dark_src2)

imwrite(dark_src2, 'teaser.png');