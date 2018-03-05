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
	pause(0.2);
	F(it) = getframe(p);
	
	delete(m);
end
hold off;

delete(p)

figure
movie(F)
