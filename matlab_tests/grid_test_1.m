clc
clear all
close all

[X,Y] = meshgrid(-pi/2:pi/100:pi/2,-pi/2:pi/100:pi/2);
C = zeros(length(X),length(Y))
C = C + 100
C(10,1) = 255;

figure(1)
hold on;
axis square;
C(50,80) = 255;
hold on;
pcolor(X,Y,C);
hold off;

% subplot(2,2,[2 4])
figure(2)
hold on
imMat = zeros(length(X), length(Y), 3);
imMat(:,:,:) = 255;

imMat(50,80,:) = 0;
imMat(length(X)-10,1,:) = 0;

imshow(imMat)
hold off

