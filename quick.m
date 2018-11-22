img = imread('/home/carson/libs/raytrix_gp_data/raytrixImages/low_light/0/CRV_01_01.png');
imgHSV = rgb2hsv(img);
imgHSV(:,:,3) = 1000*imgHSV(:,:,3)
imgHSV(:,:,3) = histeq(imgHSV(:,:,3));
imgWithGain = hsv2rgb(imgHSV);
imshow(imgWithGain)