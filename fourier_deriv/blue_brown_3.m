

I = imread('513.jpg');
grayImage = rgb2gray(I);
I=im2double(grayImage);
%b
F=fftshift(fft2(I));    % surface(abs(F))
%c
plot(abs(F))     %  plot not surf 
%d
IF=ifft2(fftshift(F));
%e
figure, imshow(IF)

fftImage = fft2(grayImage);
fftImageRealPart = real(fftImage);
[rows, columns] = size(fftImageRealPart)
lineNumber = floor(rows/2); % Middle row
oneLine = fftImageRealPart(lineNumber, :);
plot(oneLine, 'r-', 'LineWidth', 2);
grid on;