clc
clear all
close all

O = [0 0 0];
C1 = O;
vXC1 = [1 0 0]';
vYC1 = [0 1 0]';
vZC1 = [0 0 1]';

PC = [-0.5 0.5 -0.5 1]';

C2 = [0.52 1.25 -2.53];
vXC2 = [1 1 1]';
vYC2 = [0 1 1]';
vZC2 = [0 0 1]';
vXC2 = vXC2/norm(vXC2);
vYC2 = vYC2/norm(vYC2);
vZC2 = vZC2/norm(vZC2);

bot = [0 0 0];
M = [vXC2 vYC2 vZC2; bot];
tran = C2 - C1;
tran = [tran 1];
tran = tran';
M = cat(2, M, tran);
Minv = inv(M);

PC
% This operation applies the transform to 
% our point. IE, after the coordinate system has
% moved, this tells us the new world coordinates of the
% point in that system
PCt = M * PC

figure()
hold on
xlabel('x');
ylabel('y');
zlabel('z');

% axis([-3 3, -3 3, -3 3]);
axis square
plot3(C1(1), C1(2), C1(3), '.k', 'MarkerSize', 30);
plot3(C2(1), C2(2), C2(3), 'ok', 'MarkerSize', 15);
plot3(PC(1), PC(2), PC(3), '*k', 'MarkerSize', 20);
plot3(PCt(1), PCt(2), PCt(3), '*b', 'MarkerSize', 20);

hold off;

d1 = sqrt((C1(1)-PC(1))^2+(C1(2)-PC(2))^2+(C1(3)-PC(3))^2)
d2 = sqrt((C2(1)-PCt(1))^2+(C2(2)-PCt(2))^2+(C2(3)-PCt(3))^2)