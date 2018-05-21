clc
clear all
close all

sOrig = [0.7 -0.3 (0.76+0.0125)];
s = sOrig; % Only works if subject is at origin
p = [0.585996 -0.649353 0.771502];
q = [0.57607 -0.646297 0.771473];

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
plot3(p(1), p(2), p(3), '.k', 'MarkerSize', 20);
plot3(q(1), q(2), q(3), '.g', 'MarkerSize', 20);
hold off;

p = p - s;
q = q - s;
s = [0 0 0];

% Now rotate p to q
p = p - s;
q = q - s;
s = [0 0 0];

v = cross(vq, vp)
ssc = [0 -v(3) v(2); v(3) 0 -v(1); -v(2) v(1) 0];
R = eye(3) + ssc + ssc^2*(1-dot(vp,vq))/(norm(v))^2;

r = p*R;
r = r/norm(r);
r = r*norm(p);
r = r + sOrig;

s = sOrig;
p = p + s;
q = q + s;

figure(3)
xlabel('x');
ylabel('y');
zlabel('z');
hold on;
axis equal;
plot3(s(1), s(2), s(3), 'ob', 'MarkerSize', 20);
plot3(p(1), p(2), p(3), '.k', 'MarkerSize', 20);
plot3(r(1), r(2), r(3), '*k', 'MarkerSize', 30);
plot3(q(1), q(2), q(3), '.g', 'MarkerSize', 20);
hold off;

C = q;
RC = R;

fprintf('\nFrom camera extrinsics function:\n');

[R,t] = cameraPoseToExtrinsics(RC,C)

fprintf('\nManually computed:\n');
tVal = -RC*C'

fprintf('\nDifferent manually...');
RCC = -RC * C';
cM = cat(2,R,RCC);
bR = [0 0 0 1];
cM = cat(1,cM,bR);
cM


