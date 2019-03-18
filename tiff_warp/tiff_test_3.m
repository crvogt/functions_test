clc;
clear all;
close all;

p = [0.1, 0.1];

a = fminsearch(@min_warp, p)

function psnr_val = min_warp(p)
	% This method only works if the cameras are pointing in the same 
	% direction...

	tiff_base = '/home/carson/libs/store_imgs/tiff_tests/';
	tiff_file = strcat(tiff_base, '1680_DepthRay.tiff');
	src_to_warp_file = strcat(tiff_base, '1680_Raw.png');
	src_target_file = strcat(tiff_base, '1679_Raw.png');

	% Read imgs
	tiff = imread(tiff_file);
	src_to_warp = imread(src_to_warp_file);
	src_target = imread(src_target_file);

	[height, width, channels] = size(src_to_warp);

	[X, Y] = meshgrid(1:width, 1:height);


	warped = zeros(height, width, channels);

	h1 = p(1);
	h2 = p(2);
	to_X = tiff * X * h1 + X;
	to_Y = tiff * Y * h2 + Y;

	warped(:, :, 1) = interp2(double(src_to_warp(:, :, 1)), to_X, to_Y);
	

	warped = uint8(warped);
	% warped = warped + 1;

	psnr_val = -1 * psnr(warped, src_target);
	fprintf('psnr_val: %f\n', psnr_val);
end
