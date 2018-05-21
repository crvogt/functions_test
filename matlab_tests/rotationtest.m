clc
clear all
close all

A = [1 0 0];
B = [0 0 1];
T = [0.5 0 -0.5];
T = T/norm(T);
Origin = [0 0 0];

v = cross(A,B);
ssc = [0 -v(3) v(2); v(3) 0 -v(1); -v(2) v(1) 0];
R = eye(3) + ssc + ssc^2*(1-dot(A,B))/(norm(v))^2;

lineA = [0, 0, 0; A];

rotatedVec = A*R;
rT = T*R;

lineT = [0, 0, 0; T];
lineRT = [0 0 0; rT];
lineR = [0, 0, 0; rotatedVec];

figure()
xlabel('x');
ylabel('y');
zlabel('z');
hold on;
axis equal;
plot3(Origin(1), Origin(2), Origin(3), 'ob', 'MarkerSize', 20);
plot3(A(1), A(2), A(3), '*k', 'MarkerSize', 20);
plot3(rotatedVec(1), rotatedVec(2), rotatedVec(3), '*g', 'MarkerSize', 20);
plot3(rT(1), rT(2), rT(3), '*k', 'MarkerSize', 40);
plot3(T(1), T(2), T(3), '*k', 'MarkerSize', 40);
plot3(lineA(:,1), lineA(:,2), lineA(:,3));
plot3(lineT(:,1), lineT(:,2), lineT(:,3));
plot3(lineR(:,1), lineR(:,2), lineR(:,3));
plot3(lineRT(:,1), lineRT(:,2), lineRT(:,3));
hold off;