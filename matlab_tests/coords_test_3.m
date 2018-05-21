clc
clear all
close all
%Define a shape that you'll want to project

% Define a cube
% 8 points
sO = [0.5 0.5 0.5];
pts = [0 0 0; 1 0 0; 1 1 0; 0 1 0;
       0 0 1; 1 0 1; 1 1 1; 0 1 1];

% Camera definition   
C = [0.5, -3, 0.5];
f = 0.02;
senX = 1;
senY = 0.5;
PC = [1 0 0 0;
      0 1 0 0;
      0 0 1 0;
      0 0 0 1];

C2 = [0.5, -3, 2];
C = C2;

figure(1)
hold on;
% axis([-4 4, -4 4, -4 4]);
xlabel('x')
ylabel('y')
zlabel('z');
plot3(sO(1), sO(2), sO(3), '*k', 'MarkerSize', 25);
plot3(pts(:,1), pts(:,2), pts(:,3), '.k', 'MarkerSize', 30);
plot3(C(1), C(2), C(3), 'd');
plot3(C2(1), C2(2), C2(3), 'o');


cZ = sO - C;
cZ = cZ/norm(cZ);


cZ2 = sO - C2;
cZ2 = cZ2/norm(cZ2);

upV = [0 0 1];
kC = cross(upV,cZ);
kC2 = cross(upV, cZ2);

vecAngle = acos(dot(upV, cZ)) - pi/2;
vecAngle2 = acos(dot(upV, cZ2)) - pi/2;

vecAngle * 180 / pi

cY = rodrigues_rot(upV, kC, vecAngle);
cY = cY/norm(cY);

cY2 = rodrigues_rot(upV, kC2, vecAngle2);
cY2 = cY2/norm(cY2);

cX = cross(cZ, cY);
cX = cX/norm(cX);

cX2 = cross(cZ2, cY2);
cX2 = cX2/norm(cX2);


np = C + cY * 2;
np2 = C2 + cY2 * 2;

plot3(np(1), np(2), np(3), '*g', 'MarkerSize', 40)
plot3(np2(1), np2(2), np2(3), '.g', 'MarkerSize', 50);

npCheck = C2 + cZ2 * 4;

plot3(npCheck(1), npCheck(2), npCheck(3), '*b', 'MarkerSize', 40)

% Plot sensor planes
fp = C + cZ*f;
fp2 = C2 + cZ2*f;
% Center position of image plane
% But we already have the vectors

cP1 = fp + (cX*(senX/2) + cY*(senY/2));
cP2 = fp + (cX*(senX/2) + cY*(-senY/2));
cP3 = fp + (cX*(-senX/2) + cY*(senY/2));
cP4 = fp + (cX*(-senX/2) + cY*(-senY/2));
plot3(cP1(1), cP1(2), cP1(3), '.r', 'MarkerSize', 20);
plot3(cP2(1), cP2(2), cP2(3), '.r', 'MarkerSize', 20);
plot3(cP3(1), cP3(2), cP3(3), '.r', 'MarkerSize', 20);
plot3(cP4(1), cP4(2), cP4(3), '.r', 'MarkerSize', 20);

placeVec = cP1 - C;
placeVec = placeVec/norm(placeVec);
placePt = C + 10*placeVec;
placePt = [C;placePt];
plot3(placePt(:,1), placePt(:,2), placePt(:,3));

placeVec = cP2 - C;
placeVec = placeVec/norm(placeVec);
placePt = C + 10*placeVec;
placePt = [C;placePt];
plot3(placePt(:,1), placePt(:,2), placePt(:,3));

placeVec = cP3 - C;
placeVec = placeVec/norm(placeVec);
placePt = C + 10*placeVec;
placePt = [C;placePt];
plot3(placePt(:,1), placePt(:,2), placePt(:,3));

placeVec = cP4 - C;
placeVec = placeVec/norm(placeVec);
placePt = C + 10*placeVec;
placePt = [C;placePt];
plot3(placePt(:,1), placePt(:,2), placePt(:,3));
hold off;

% We have the axes of the camera in terms of world coordinates
cX;
cY;
cZ;
% We need to create a transform matrix
% Defines local to world 
M = [cX' cY' cZ'];
tran = C';
M = [M tran];
M = [M; 0 0 0 1];

% world to local
Minv = inv(M);
cP1l = Minv*[cP1 1]';
cP2l = Minv*[cP2 1]';
cP3l = Minv*[cP3 1]';
cP4l = Minv*[cP4 1]';

% camera local plot
origin = [0 0 0];
% figure(2)
% hold on
% % axis([-2 2 -2 2 -2 2])
% axis equal
% plot3(cP1l(1), cP1l(2), cP1l(3), '.r', 'MarkerSize', 20);
% plot3(cP2l(1), cP2l(2), cP2l(3), '.r', 'MarkerSize', 20);
% plot3(cP3l(1), cP3l(2), cP3l(3), '.r', 'MarkerSize', 20);
% plot3(cP4l(1), cP4l(2), cP4l(3), '.r', 'MarkerSize', 20);
% plot3(origin(1), origin(2), origin(3), '.k', 'MarkerSize', 25);
% hold off

% Converting existing points to camera coordinates
sO = [0.5 0.5 0.5];
pts = [0 0 0; 1 0 0; 1 1 0; 0 1 0;
       0 0 1; 1 0 1; 1 1 1; 0 1 1];
   
sOl = Minv*[sO 1]';
pts1l = Minv * [pts(1,:) 1]';
pts2l = Minv * [pts(2,:) 1]';
pts3l = Minv * [pts(3,:) 1]';
pts4l = Minv * [pts(4,:) 1]';
pts5l = Minv * [pts(5,:) 1]';
pts6l = Minv * [pts(6,:) 1]';
pts7l = Minv * [pts(7,:) 1]';
pts8l = Minv * [pts(8,:) 1]';

% All points now in local coordinates
points = [pts1l(1)/pts1l(3) pts1l(2)/pts1l(3);
          pts2l(1)/pts2l(3) pts2l(2)/pts2l(3);
          pts3l(1)/pts3l(3) pts3l(2)/pts3l(3);
          pts4l(1)/pts4l(3) pts4l(2)/pts4l(3);
          pts5l(1)/pts5l(3) pts5l(2)/pts5l(3);
          pts6l(1)/pts6l(3) pts6l(2)/pts6l(3);
          pts7l(1)/pts7l(3) pts7l(2)/pts7l(3);
          pts8l(1)/pts8l(3) pts8l(2)/pts8l(3)];

% fingers crossed
figure(3)
hold on

[rows, cols] = size(points); 
senX
senY

for iter = 1:rows
    if (abs(points(iter,1)) <= senX/2) & (abs(points(iter,2)) <= senY/2)
        plot(points(iter,1), points(iter,2), '.k', 'MarkerSize', 20)
    else
        fprintf('Point outside of sensor range x:%f y:%f\n', points(iter,1), points(iter,2));
    end
end

% plot(pr2(1), pr2(2), '.k', 'MarkerSize', 20)
% plot(pr3(1), pr3(2), '.k', 'MarkerSize', 20)
% plot(pr4(1), pr4(2), '.k', 'MarkerSize', 20)
% plot(pr5(1), pr5(2), '.k', 'MarkerSize', 20)
% plot(pr6(1), pr6(2), '.k', 'MarkerSize', 20)
% plot(pr7(1), pr7(2), '.k', 'MarkerSize', 20)
% plot(pr8(1), pr8(2), '.k', 'MarkerSize', 20)
hold off;
