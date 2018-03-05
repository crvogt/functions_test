clc
clear all
close all

pose = [0 0 0];

radius = 1;

vector1 = [1 0 0];
vector2 = [0 0 1];

point1 = pose + radius*vector1;
point2 = pose + radius*vector2;

figure(1)
hold on;
axis equal;
xlabel('x')
ylabel('y')
zlabel('z')

plot3(pose(1), pose(2), pose(3), '*k', 'MarkerSize', 20);
plot3(point1(1), point1(2), point1(3), 'db', 'MarkerSize', 20);
plot3(point2(1), point2(2), point2(3), 'dr', 'MarkerSize', 20);
xS = [pose(1) point1(1)];
yS = [pose(2) point1(2)];
zS = [pose(3) point1(3)];
plot3(xS, yS, zS);
xS = [pose(1) point2(1)];
yS = [pose(2) point2(2)];
zS = [pose(3) point2(3)];
plot3(xS, yS, zS);

vector3 = cross(vector1, vector2);
point3 = pose + radius*vector3;
plot3(point3(1), point3(2), point3(3), 'dg', 'MarkerSize', 20);
xS = [pose(1) point3(1)];
yS = [pose(2) point3(2)];
zS = [pose(3) point3(3)];
plot3(xS, yS, zS);

vector4 = rodrigues_rot(vector2, vector3, -pi/8);
vector4 = vector4 / norm(vector4);
point4 = pose + radius*vector4;
plot3(point4(1), point4(2), point4(3), 'sk', 'MarkerSize', 35);
xS = [pose(1) point4(1)];
yS = [pose(2) point4(2)];
zS = [pose(3) point4(3)];
plot3(xS, yS, zS);

view(3);

hold off;