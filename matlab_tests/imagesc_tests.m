clc
clear all
close all

data = zeros(20);
for y = 1:20
	for x = 1:20
		data(x,y) = x*y;
	end
end

figure(1);
imagesc(data);