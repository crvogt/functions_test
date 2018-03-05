clc
clear all
close all

radius = 0.01;

% Camera matrix (can be found in data file)
K = [543.141720, 0.000000, 316.660464;
	 0.000000, 543.515325, 261.440378
	 0.000000, 0.000000, 1.000000];
% [fx 0 cx
%  0 fy cy
%  0 0 1]

fx = K(1,1)
fy = K(2,2)

% fov while testing
fov = 75/2; % in degrees

% Image sensor dimensions
% from website
H = 5265; % in micro meters 
W = 5345;

% in pixels
h = 480;
w = 640;

H = 0.005265; % aka 5.2 mm
W = 0.005345;

Fx = fx * W / w;
fprintf('Focal length based on sensor only: %f', Fx);

fov = pi * fov / 180;
Fx = (W/2) / tan(fov);
fprintf('\nFocal length based on fov: %f\n', Fx);


stepX = W/w;
x = 0:stepX:(W-stepX);
stepY = H/h;
y = 0:stepY:(H-stepY);

noOfPix = length(x) * length(y);

fprintf('\nNumber of pixels: %d \n', noOfPix);

[X Y] = meshgrid(x, y);
Z = zeros(length(x), length(y));

plot3(X, Y, Z, '.k')
xlabel('x')
ylabel('y')
zlabel('z')

camCenter = [W/2 H/2 Fx]
plot3(camCenter(1), camCenter(2), camCenter(3), '*g', 'MarkerSize', 20);

for it = 1:523:noOfPix
	% Draw a line from camCenter through point in image sensor
	% Vector is starting point subtracted from ending point (B - A)
	newVect = [X(it) - camCenter(1), Y(it) - camCenter(2), Z(it) - camCenter(3)];
	newVect = newVect / norm(newVect);
	spherePt = camCenter + radius*newVect;
	lineX = [camCenter(1), spherePt(1)];
	lineY = [camCenter(2), spherePt(2)];
	lineZ = [camCenter(3), spherePt(3)];
	plot3(lineX, lineY, lineZ, 'b');
	% pause(0.1);
	fprintf('\npixNo: %d', it);
end

[x y z] = sphere;

mesh(x.*radius+camCenter(1), y.*radius+camCenter(2), z.*radius+camCenter(3),'edgecolor','k','FaceAlpha', 0.1);



cameraVec = [0 1 0];
upVec = [1 0 0];

cameraVec = cameraVec/norm(cameraVec);

cameraCenter = [0.5 0.5 0.5];

radius = 2;

newPt = cameraCenter + radius*cameraVec;

figure(1)

axis([-4 4 -4 4 -4 4])

hold on;

plot3(cameraCenter(1), cameraCenter(2), cameraCenter(3), 'db', 'MarkerSize', 20);
plot3(newPt(1), newPt(2), newPt(3), '*k', 'MarkerSize', 20);
% Plot a line
x = [cameraCenter(1), newPt(1)];
y = [cameraCenter(2), newPt(2)];
z = [cameraCenter(3), newPt(3)];

plot3(x, y, z, 'b');

xlabel('x')
ylabel('y')
zlabel('z')

hold off;
