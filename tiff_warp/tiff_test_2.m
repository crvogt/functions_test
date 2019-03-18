clc;
clear all;
close all;

% This method only works if the cameras are pointing in the same 
% direction...

tiff_base = '/home/carson/libs/store_imgs/tiff_tests/';
tiff_file = strcat(tiff_base, '1680_DepthRay.tiff');
src_to_warp_file = strcat(tiff_base, '1680_Raw.png');
src_target_file = strcat(tiff_base, '1679_Raw.png');

% Read imgs
fprintf('Loading images...\n');
tiff = imread(tiff_file);
src_to_warp = imread(src_to_warp_file);
src_target = imread(src_target_file);

psnr_val = psnr(src_to_warp, src_target);

fprintf('Initial psnr: %f\n', psnr_val);

[height, width, channels] = size(src_to_warp);

[X, Y] = meshgrid(1:width, 1:height);

% to_Y = tiff;
% to_X = tiff;

% generate synthetic test data, for experimenting
% to_X = tiff*X;   % an arbitrary flow field, in this case
% to_Y = tiff*Y;   % representing shear
p1 = 0.1;
p2 = 0.1;

while(error < 12.0)
	to_X = tiff * X * 0.1 + X;
	to_Y = tiff * Y * 0.1 + Y;

	fprintf('\nWarping...\n');

	warped = zeros(height, width, channels);

	for i = 1:channels
		warped(:, :, i) = interp2(double(src_to_warp(:, :, i)), to_X, to_Y);
	end

	warped = uint8(warped);
	% warped = warped + 1;

	imshow(warped);

	psnr_val = psnr(warped, src_target);
	fprintf('\npsnr: %f\n', psnr_val);
end

