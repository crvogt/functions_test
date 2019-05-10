addpath('../')

% imgPath = '/home/carson/libs/gray_to_png/0034035116/plant_processed.png'
base_loc = '/media/carson/SAMSUNG/var_exp_val_1/2/gif_imgs_light/processed/'
writeDir = strcat(base_loc, 'sais/');

list = dir([base_loc, '*', '.png'])
cont_names = setdiff({list.name}, {'.', '..'})

for k = 1:length(cont_names)
	mkdir(strcat(writeDir, num2str(k+19)));
	write_to = strcat(writeDir, num2str(k+19));

	LF = get_sub_ap_03(strcat(base_loc, cont_names{k}));
	LFWriteOutDepthSAI_crv(LF, write_to);
end
