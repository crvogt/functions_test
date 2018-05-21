clc
clear all
close all

s = [1 1 1]; % Only works if subject is at origin
p = [3 2 1];
q = [2 4 0];
vp = s - p;
vp = vp/norm(vp);
vq = s - q;
vq = vq/norm(vq);

figure(1)
xlabel('x');
ylabel('y');
zlabel('z');
hold on;
axis equal;
plot3(s(1), s(2), s(3), 'ob', 'MarkerSize', 20);
plot3(p(1), p(2), p(3), '*k', 'MarkerSize', 20);
plot3(q(1), q(2), q(3), '*g', 'MarkerSize', 20);
hold off;

% Now rotate p to q
v = cross(vq, vp);
ssc = [0 -v(3) v(2); v(3) 0 -v(1); -v(2) v(1) 0];
R = eye(3) + ssc + ssc^2*(1-dot(vp,vq))/(norm(v))^2

r = p*R;
r = r/norm(r);
r = r*norm(p);

figure(2)
xlabel('x');
ylabel('y');
zlabel('z');
hold on;
axis equal;
plot3(s(1), s(2), s(3), 'ob', 'MarkerSize', 20);
plot3(p(1), p(2), p(3), '*k', 'MarkerSize', 20);
plot3(r(1), r(2), r(3), '*k', 'MarkerSize', 40);
plot3(q(1), q(2), q(3), '*g', 'MarkerSize', 20);
hold off;

% Now rotate q to p

v = cross(vp, vq);
ssc = [0 -v(3) v(2); v(3) 0 -v(1); -v(2) v(1) 0];
R = eye(3) + ssc + ssc^2*(1-dot(vp,vq))/(norm(v))^2

r = q*R;
r = r/norm(r);
r = r*norm(q);

figure(3)
xlabel('x');
ylabel('y');
zlabel('z');
hold on;
axis equal;
plot3(s(1), s(2), s(3), 'ob', 'MarkerSize', 20);
plot3(p(1), p(2), p(3), '*k', 'MarkerSize', 20);
plot3(r(1), r(2), r(3), '*g', 'MarkerSize', 40);
plot3(q(1), q(2), q(3), '*g', 'MarkerSize', 20);
hold off;