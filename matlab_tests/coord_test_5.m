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
C = [1, -3, 0.5];
f = 0.02;
senX = 0.015;
senY = 0.012;
PC = [1 0 0 0;
      0 1 0 0;
      0 0 1 0;
      0 0 0 1];

subplot(1,3,1)
hold on;
% axis([-4 4, -4 4, -4 4]);
xlabel('x')
ylabel('y')
zlabel('z');
plot3(sO(1), sO(2), sO(3), '*k', 'MarkerSize', 25);
plot3(pts(:,1), pts(:,2), pts(:,3), '.k', 'MarkerSize', 30);
plot3(C(1), C(2), C(3), 'd');

cZ = sO - C;
cZ = cZ/norm(cZ);

upV = [0 0 1];
kC = cross(upV,cZ);

vecAngle = acos(dot(upV, cZ)) - pi/2;

vecAngle * 180 / pi;

cY = rodrigues_rot(upV, kC, vecAngle);
cY = cY/norm(cY);

cX = cross(cZ, cY);
cX = cX/norm(cX);

np = C + cY * 2;

% Plot sensor planes
fp = C + cZ*f;
% Center position of image plane
% But we already have the vectors

cP = [fp + (cX*(senX/2) + cY*(senY/2));
      fp + (cX*(senX/2) + cY*(-senY/2));
      fp + (cX*(-senX/2) + cY*(senY/2));
      fp + (cX*(-senX/2) + cY*(-senY/2))];

[rows, cols] = size(cP); 
for iter = 1:rows
    plot3(cP(iter,1), cP(iter,2), cP(iter,3), '.r', 'MarkerSize', 20);
end
  
for iter = 1:rows
    placeVec = cP(iter,:) - C;
    placeVec = placeVec/norm(placeVec);
    placePt = C + 10*placeVec;
    placePt = [C;placePt];
    plot3(placePt(:,1), placePt(:,2), placePt(:,3));
end

% Plot lines from points to C
for iter = 1:length(pts)
   pairX = [C(1) pts(iter,1)];
   pairY = [C(2) pts(iter,2)];
   pairZ = [C(3) pts(iter,3)];
   plot3(pairX, pairY, pairZ) 
end
view(3)
hold off


% We need to create a transform matrix
% Defines local to world 
M = [cX' cY' cZ'];
tran = C';
% tran(3) = tran(3) - f;
% tran = fp';
M = [M tran];
M = [M; 0 0 0 1];

% world to local
Minv = inv(M);
cPl = [(Minv*[cP(1,:) 1]')';
       (Minv*[cP(2,:) 1]')';
       (Minv*[cP(3,:) 1]')';
       (Minv*[cP(4,:) 1]')'];


% Converting existing points to camera coordinates
sO = [0.5 0.5 0.5];
pts = [0 0 0; 1 0 0; 1 1 0; 0 1 0;
       0 0 1; 1 0 1; 1 1 1; 0 1 1];
   
sOl = Minv*[sO 1]';

% Putting into camera coordinates
ptsl = [(Minv * [pts(1,:) 1]')';
        (Minv * [pts(2,:) 1]')';
        (Minv * [pts(3,:) 1]')';
        (Minv * [pts(4,:) 1]')';
        (Minv * [pts(5,:) 1]')';
        (Minv * [pts(6,:) 1]')';
        (Minv * [pts(7,:) 1]')';
        (Minv * [pts(8,:) 1]')'];

% All points now in local coordinates
points = [ptsl(1,1)/ptsl(1,3) ptsl(1,2)/ptsl(1,3);
          ptsl(2,1)/ptsl(2,3) ptsl(2,2)/ptsl(2,3);
          ptsl(3,1)/ptsl(3,3) ptsl(3,2)/ptsl(3,3);
          ptsl(4,1)/ptsl(4,3) ptsl(4,2)/ptsl(4,3);
          ptsl(5,1)/ptsl(5,3) ptsl(5,2)/ptsl(5,3);
          ptsl(6,1)/ptsl(6,3) ptsl(6,2)/ptsl(6,3);
          ptsl(7,1)/ptsl(7,3) ptsl(7,2)/ptsl(7,3);
          ptsl(8,1)/ptsl(8,3) ptsl(8,2)/ptsl(8,3)];

      
points = points * f;
% fingers crossed
% plotting points on image plane
subplot(1,3,2)
hold on
[rows, cols] = size(points); 
% fprintf('SensorX: %f, SensorY: %f\n', senX, senY);
for iter = 1:rows
    if (abs(points(iter,1)) <= senX/2) & (abs(points(iter,2)) <= senY/2)
        plot(points(iter,1), points(iter,2), '.k', 'MarkerSize', 20)
    else
        fprintf('Point outside of sensor range x:%f y:%f\n', points(iter,1), points(iter,2));
    end
end
hold off

% camera local plot
origin = [0 0 0];
subplot(1,3,3)
hold on
% axis([-2 2 -2 2 -2 2])
axis equal
[lrows, ~] = size(cPl);

for iter = 1:lrows
    plot3(cPl(iter,1), cPl(iter,2), cPl(iter,3), '.r', 'MarkerSize', 20);
end
plot3(origin(1), origin(2), origin(3), '.k', 'MarkerSize', 25);

for iter = 1:rows
    plot3(points(iter,1), points(iter,2), 0.02, '.b', 'MarkerSize', 20)
end

hold off