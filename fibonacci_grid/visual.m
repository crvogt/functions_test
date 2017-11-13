clc
clear all 
close all

% 
% 
% figure(1)
% hold on;
% 
% x =0.179054 
% y =-0.441186 
% z =0.788875
% plot3(x,y,z, '*','MarkerSize',10);
% x =0.143036 
% y =-0.00299087 
% z =0.821625
% plot3(x,y,z, '*','MarkerSize',10);
% x= 0.570197 
%  y =0.0675551 
%  z =0.854375
% plot3(x,y,z, '*','MarkerSize',10);
%  x =0.672256 
%  y =-0.341399 
%  z =0.887125
%  plot3(x,y,z, '*','MarkerSize',10);
%  x =0.288408 
%  y =-0.470341 
%  z =0.919875
%  plot3(x,y,z, '*','MarkerSize',10);
%  x =0.13902 
%  y =-0.118141 
%  z =0.952625
%  plot3(x,y,z, '*','MarkerSize',10);
%  x =0.453439 
%  y =0.0430735 
%  z =0.985375
%  plot3(x,y,z, '*','MarkerSize',10);
%  x =0.614825 
%  y =-0.227838 
%  z =1.01812
%  plot3(x,y,z, '*','MarkerSize',10);
%  x =0.392871 
%  y =-0.372374 
%  z =1.05087
%  plot3(x,y,z, '*','MarkerSize',10);
%  x =0.297847 
%  y =-0.204724 
%  z =1.08362
% plot3(x,y,z, '*','MarkerSize',10);
% hold off;

figure(1)
hold on;
xlabel('x')
ylabel('y')
zlabel('z')
axis([-1 1 -1 1 -1 1])
armLocX = 0.8;
armLocY = -0.1;
armLocZ = 0.8;

plot3(armLocX, armLocY, armLocZ, '*','MarkerSize', 10);

subjectX = 0.7;
subjectY = 0;
subjectZ = 0.7;

plot3(subjectX, subjectY, subjectZ, '*', 'MarkerSize', 10);

hold off;

yaw = atan((subjectY - armLocY)/(subjectX - armLocX))
pitch = asin(subjectZ - armLocZ)

