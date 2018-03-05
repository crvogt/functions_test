clc
clear all
close all

x = 1:10;
y = zeros(length(x));
y = y + 1;

p = figure(1);
hold on;
axis([0 10 0 2]);

for it = 1:length(x)
	m = plot(x(it), y(it), '*k', 'MarkerSize', 10);
	pause(1);
	F = getframe(p);
	if(it == 1)
		fArray = [F];
	else 
		fArray = [fArray; F];
	end
	delete(m);
end
hold off;

delete(p)

figure
for it = 1:length(fArray)
	imshow(fArray(it).cdata)
	pause(1);
end