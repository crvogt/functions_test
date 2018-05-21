function [fullLF, inputLF] = ReadIllumImages(scenePath)

numImgsX = 14;
numImgsY = 14;

%%% converting the extracted light field to a different format
% This is the input light field image
inputImg = im2double(imread(scenePath));
% imshow(inputImg)


h = size(inputImg, 1) / numImgsY;
w = size(inputImg, 2) / numImgsX;

fprintf('\nh value %d', h);
fprintf('\nw value %d', w);

fullLF = zeros(h, w, 3, numImgsY, numImgsX);
for ax = 1 : numImgsX
    for ay = 1 : numImgsY
        fullLF(:, :, :, ay, ax) = inputImg(ay:numImgsY:end, ax:numImgsX:end, :);
  %       fprintf('\nShowing portion of fullLF\n');
		% singleImage = fullLF(:,:,:,ay,ax);
		% px = figure(1);
		% imshow(singleImage);
		% for i = 1:3
		% 	fprintf('\npaused for %d', i);
		% 	pause(1)
		% end
		% clf(px)
    end
end

if (h == 375 && w == 540)
	fprintf('\nPadding Array fullLF')
    fullLF = padarray(fullLF, [1, 1], 0, 'post');
else
	fprintf('\nNo Padding...');
end

if (h == 375 && w == 541)
	fprintf('\nPadding Array fullLF w = ')
    fullLF = padarray(fullLF, [1, 0], 0, 'post');
else
	fprintf('\nStill no padding\n');
end

fullLF = fullLF(:, :, :, 4:11, 4:11); % we only take the 8 middle images
inputLF = fullLF(:, :, :, [1, 8], [1, 8]); % we use the four corner sub-aperture images as our input

