clc;
clear all;
close all;

% This method only works if the cameras are pointing in the same 
% direction...

tiff_base = '/home/carson/libs/store_imgs/tiff_test/';
tiff_file = strcat(tiff_base, '1680_DepthRay.tiff');
src_to_warp_file = strcat(tiff_base, '1680_Raw.png');
src_target_file = strcat(tiff_base, '1679_Raw.png');

% Read imgs
fprintf('Loading images...\n');
tiff = imread(tiff_file);
src_to_warp = imread(src_to_warp_file);
src_target = imread(src_target_file);

[height, width, channels] = size(src_to_warp);

[X, Y] = meshgrid(1:width, 1:height);

to_Y = Y + 1;
to_X = X + 1;

fprintf('\nWarping...\n');

warped = zeros(height, width, channels);

for i = 1:channels
	warped(:, :, i) = interp2(X, Y, single(src_to_warp(:, :, i)), to_X, to_Y, 'cubic', nan);
end

warped = uint8(warped);

imshow(warped);

psnr = psnr(warped, src_target);
fprintf('\npsnr: %f\n', psnr);