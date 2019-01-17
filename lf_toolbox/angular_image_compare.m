% Pull from dark images
% Compare with enhanced and ref
clc
clear all
close all

base_write_file = '/home/carson/libs/raytrix_gp_data/raytrixImages/low_light_angular';
% base_read_file = '/home/carson/libs/raytrix_gp_data/raytrixImages/low_light_proc/devignette';
base_read_file = '/home/carson/libs/store_imgs/devignette_out/'
num_imgs = 19;

for iVal = 0:num_imgs
	% enhance
	imgPath = strcat(base_read_file, num2str(iVal), '/enh.png');
	LF = get_sub_ap(imgPath);

	pxStart = 6;
	pxEnd = 20;
	pxDist = 1;
	imgCount = 0;
	for iter = pxStart:pxDist:pxEnd
		for jter = pxStart:pxDist:pxEnd
			% img = uint16(squeeze(LF(iter,jter,:,:,:)));
			img = uint8(squeeze(LF(iter, jter, :, :, :)));
			filename = strcat(base_write_file,'/enhance/', num2str(iVal));
			if ~exist(filename)
				mkdir(filename)
			end
			filename = strcat(filename, '/', num2str(imgCount), '.png');

			imwrite(img, filename)
			imgCount = imgCount + 1;
		end
	end
end

% for iVal = 0:num_imgs
% 	% ref
% 	imgPath = strcat(base_read_file, '_ref/', num2str(iVal), '.png');
% 	LF = get_sub_ap(imgPath);

% 	pxStart = 6;
% 	pxEnd = 20;
% 	pxDist = 1;
% 	imgCount = 0;
% 	for iter = pxStart:pxDist:pxEnd
% 		for jter = pxStart:pxDist:pxEnd
% 			img = uint16(squeeze(LF(iter,jter,:,:,:)));
% 			% img = uint8(squeeze(LF(iter, jter, :, :, :)));
% 			filename = strcat(base_write_file,'/ref/', num2str(iVal));
% 			if ~exist(filename)
% 				mkdir(filename)
% 			end
% 			filename = strcat(filename, '/', num2str(imgCount), '.png');

% 			imwrite(img, filename)
% 			imgCount = imgCount + 1;
% 		end
% 	end
% end

% Gain
% for iVal = 0:num_imgs
% 	imgPath = strcat(base_read_file, '_gain/', num2str(iVal), '/gain.png');
% 	LF = get_sub_ap(imgPath);

% 	pxStart = 6;
% 	pxEnd = 20;
% 	pxDist = 1;
% 	imgCount = 0;
% 	for iter = pxStart:pxDist:pxEnd
% 		for jter = pxStart:pxDist:pxEnd
% 			% img = uint16(squeeze(LF(iter,jter,:,:,:)));
% 			img = uint8(squeeze(LF(iter, jter, :, :, :)));
% 			filename = strcat(base_write_file,'/gain/', num2str(iVal));
% 			if ~exist(filename)
% 				mkdir(filename)
% 			end
% 			filename = strcat(filename, '/', num2str(imgCount), '.png');

% 			imwrite(img, filename)
% 			imgCount = imgCount + 1;
% 		end
% 	end
% end

% % NPE
% for iVal = 0:num_imgs
% 	imgPath = strcat(base_read_file, '_npe/', num2str(iVal), '/npe.png');
% 	LF = get_sub_ap(imgPath);

% 	pxStart = 6;
% 	pxEnd = 20;
% 	pxDist = 1;
% 	imgCount = 0;
% 	for iter = pxStart:pxDist:pxEnd
% 		for jter = pxStart:pxDist:pxEnd
% 			% img = uint16(squeeze(LF(iter,jter,:,:,:)));
% 			img = uint8(squeeze(LF(iter, jter, :, :, :)));
% 			filename = strcat(base_write_file,'/npe/', num2str(iVal));
% 			if ~exist(filename)
% 				mkdir(filename)
% 			end
% 			filename = strcat(filename, '/', num2str(imgCount), '.png');

% 			imwrite(img, filename)
% 			imgCount = imgCount + 1;
% 		end
% 	end
% end

% % Lime
% for iVal = 0:num_imgs
% 	imgPath = strcat(base_read_file, '_lime/', num2str(iVal), '/lime.png');
% 	LF = get_sub_ap(imgPath);

% 	pxStart = 6;
% 	pxEnd = 20;
% 	pxDist = 1;
% 	imgCount = 0;
% 	for iter = pxStart:pxDist:pxEnd
% 		for jter = pxStart:pxDist:pxEnd
% 			% img = uint16(squeeze(LF(iter,jter,:,:,:)));
% 			img = uint8(squeeze(LF(iter, jter, :, :, :)));
% 			filename = strcat(base_write_file,'/lime/', num2str(iVal));
% 			if ~exist(filename)
% 				mkdir(filename)
% 			end
% 			filename = strcat(filename, '/', num2str(imgCount), '.png');

% 			imwrite(img, filename)
% 			imgCount = imgCount + 1;
% 		end
% 	end
% end