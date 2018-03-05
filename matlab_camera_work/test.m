clc
clear all
close all

vectOrig = [1 -1 0];
vectOrig = vectOrig/norm(vectOrig);

posePt = [0 0 0];

radius = 1;

newPt = posePt + vectOrig*radius;

x = [posePt(1) newPt(1)];
y = [posePt(2) newPt(2)];
z = [posePt(3) newPt(3)];

figure(1)
hold on;

axis([-2 2 -2 2 -2 2]);

plot3(posePt(1), posePt(2), posePt(3), '*k', 'MarkerSize', 20);
plot3(newPt(1), newPt(2), newPt(3), 'dr', 'MarkerSize', 20);
plot3(x, y, z, 'b');

view(3);

xlabel('x')
ylabel('y')
zlabel('z')

theta = atan(newPt(2)/newPt(1));
theta = theta * 180/pi
phi = acos(newPt(3)/radius);
phi = phi * 180/pi



hold off;
