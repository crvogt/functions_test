% Pull from dark images
% Compare with enhanced and ref
clc
clear all
close all

base_write_file = '/home/carson/libs/raytrix_gp_data/raytrixImages/low_light_single';
base_read_file = '/home/carson/libs/raytrix_gp_data/raytrixImages/low_light_proc/devignette'
num_imgs = 19;

% for iVal = 0:num_imgs
% 	% dark
% 	imgPath = strcat(base_read_file, '/', num2str(iVal), '.png');
% 	LF = get_sub_ap(imgPath);

% 	iter = 13;
% 	jter = 13;
% 	img = uint16(squeeze(LF(iter,jter,:,:,:)));
% 	% img = uint8(squeeze(LF(iter, jter, :, :, :)));
% 	filename = strcat(base_write_file,'/dark/', num2str(iVal), '.png');

% 	imwrite(img, filename)
% end

for iVal = 0:num_imgs
	% enhance
	imgPath = strcat(base_read_file, '_enhance/', num2str(iVal), '.png');
	LF = get_sub_ap(imgPath);

	iter = 13;
	jter = 13;
	img = uint16(squeeze(LF(iter,jter,:,:,:)));
	% img = uint8(squeeze(LF(iter, jter, :, :, :)));
	filename = strcat(base_write_file,'/enhance/', num2str(iVal), '.png');

	imwrite(img, filename)
end

for iVal = 0:num_imgs
	% ref
	imgPath = strcat(base_read_file, '_ref/', num2str(iVal), '.png');
	LF = get_sub_ap(imgPath);

	iter = 13;
	jter = 13;
	img = uint16(squeeze(LF(iter,jter,:,:,:)));
	% img = uint8(squeeze(LF(iter, jter, :, :, :)));
	filename = strcat(base_write_file,'/ref/', num2str(iVal), '.png');

	imwrite(img, filename)
end