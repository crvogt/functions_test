src1 = imread('/home/carson/opencv_proj/feature_matching/flann_matching/data/513.jpg');
src2 = imread('/home/carson/opencv_proj/feature_matching/flann_matching/data/530.jpg');

gray1 = rgb2gray(src1);
gray2 = rgb2gray(src2);

disparityMap = disparity(gray1, gray2);

figure();
imshow(disparityMap, [0, 64]);
title('Disparity Map');
colormap jet
colorbar