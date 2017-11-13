clc
close all
clear all

x = -4*pi:0.1:4*pi;

f = cos(0) + x*0;

figure(1)
hold on;

plot(x, f)
plot(x, cos(x))

axis([-10 10 -4 4])

hold off;
