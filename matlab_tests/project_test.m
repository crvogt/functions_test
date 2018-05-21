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
senX = 0.015;
senY = 0.012;
PC = [1 0 0 0;
      0 1 0 0;
      0 0 1 0;
      0 0 0 1];

C2 = [0.5, -3, 2];

figure()
hold on;
axis([-4 4, -4 4, -4 4]);
xlabel('x')
ylabel('y')
zlabel('z');
plot3(sO(1), sO(2), sO(3), '*k', 'MarkerSize', 25);
plot3(pts(:,1), pts(:,2), pts(:,3), '.k', 'MarkerSize', 30);
plot3(C(1), C(2), C(3), 'd');
plot3(C2(1), C2(2), C2(3), 'o');


% Find Rc and t for the two cameras, or from C to C2
vC = sO - C;
vC = vC/norm(vC);

vC2 = sO - C2;
vC2 = vC2/norm(vC2);

% Now rotate from C1 to C2
v = cross(vC, vC2);

% Now get R
ssc = [0 -v(3) v(2); v(3) 0 -v(1); -v(2) v(1) 0];
R = eye(3) + ssc + ssc^2*(1-dot(vC,vC2))/(norm(v))^2;

t = C2 - C %?
t = t';

r = C2*R;
r = r/norm(r);
r = r*norm(C2);

plot3(r(1), r(2), r(3), 'xk', 'MarkerSize' , 30);

bot = [0 0 0 1];
M = cat(2,R,t);
M = cat(1,M,bot)

PC2 = PC * M;

hold off;





