function anLF = ReadLightFieldImages(imgPath, parmPath)

global param;

% imgPath(1){'/media/carson/WDPassport/deep_learn/pr2_dataset/all_training_data/train_set_1/internal_points/5470.jpg'}
% parmPath(1){'/media/carson/WDPassport/deep_learn/pr2_dataset/all_training_data/train_set_1/internal_points/5470_-0_8253887_1_081807.mat'}


height = param.height;
width = param.width;

numImages = length(imgPath);

% anLF = zeros([height, width, 5*numImages]); %h, w, rgbtp
counter = 1;

% fprintf('\nnumImages: %d\n',)

for it = 1:numImages
	tempImg = im2double(imread(imgPath{it}));
	load(parmPath{it});
	anLF(:, :, counter:(counter+2)) = tempImg;
	anLF(:, :, (counter+3):(counter+4)) = locMat;
	counter = counter + 5;
	% prompt = 'Checked the LF inputs?';
	% str = input(prompt, 's');
	% if str == 'n'
	% 	error('Then you better check the input sizes!');
	% else 
	% 	fprintf('\nPausing\n');
	% 	pause(30);
	% end
end

fprintf('\nLF size: %d\n', numImages)

% pause(10)


