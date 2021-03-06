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

to_Y = Y + tiff * 10000;
to_X = X + tiff * 10000;

fprintf('\nWarping...\n');

warped = zeros(height, width, channels);

min(min(tiff))
max(max(tiff))

for i = 1:channels
	warped(:, :, i) = interp2(X, Y, single(src_to_warp(:, :, i)), to_X, to_Y, 'cubic', nan);
end

warped = uint8(warped);
figure(1)
subplot(1,3,1)
imshow(warped);
subplot(1,3,2)
imshow(src_target);
subplot(1,3,3)
imshow(src_to_warp);

psnr_val = psnr(warped, src_target);
fprintf('\npsnr: %f\n', psnr_val);