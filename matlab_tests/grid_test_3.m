clc
clear all
close all

testIm = zeros(10, 10, 3);
testIm(1:5,1:5, :) = 255;

% figure(1)
% hold on;
image(testIm)
% image(testIm,'CDataMapping','scaled')
% hold off;

imageArr = repmat(testIm, [1 1 1 100*100]);

p = figure(2)
hold on;
montage(imageArr);
hold off;

% Attempting to adjust display size of image
truesize(p)

% figure(3)
% hold on;
% subplot(2,2,4)




% The following is really just too slow
% Attempting to initialize array of subplots
% imgSide = 100

% h = gobjects(imgSide,imgSide);


% for iter = 1:(imgSide*imgSide)
% 	100*(iter / (imgSide^2))
% 	% subplot(imgSide,imgSide,iter);
% 	% image(testIm);

% 	% % Set the 'visible' property 'off'
% 	% ax = gca;
% 	% ax.Visible = 'off';


% 	h(iter) = subplot(imgSide,imgSide,iter);

% end
% hold off;