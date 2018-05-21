



% TODO: set the first camera position as the origin
% Next, calculate the vectors to the subject,
% Then calculate the camera matrices.
% Move everything  back



clc
clear all
close all

sOrig = [0.7 -0.3 (0.76+0.0125)];
s = sOrig; % Only works if subject is at origin
q1 = [0.585996 -0.649353 0.771502];
q2 = [0.57607 -0.646297 0.771473];

origin = q1;

s = s - q1
q2 = q2 - q1
q1 = q1 - q1


vqInitial = s - q1;
vqInitial = vqInitial/norm(vqInitial)
vq = s - q2;
vq = vq/norm(vq)

% Now rotate from q1(origin) to q2

v = cross(vqInitial, vq)
ssc = [0 -v(3) v(2); v(3) 0 -v(1); -v(2) v(1) 0];
R = eye(3) + ssc + ssc^2*(1-dot(vqInitial,vq))/(norm(v))^2;

r = q2*R;
r = r/norm(r);
r = r*norm(q2);
% r = r + sOrig;

figure(1)
xlabel('x');
ylabel('y');
zlabel('z');
hold on;
axis equal;
plot3(s(1), s(2), s(3), 'ob', 'MarkerSize', 20);
plot3(q1(1), q1(2), q1(3), '.b', 'MarkerSize', 20);
plot3(q2(1), q2(2), q2(3), '.k', 'MarkerSize', 20);
plot3(r(1), r(2), r(3), '*k', 'MarkerSize', 30);
hold off;

C = q1;
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


