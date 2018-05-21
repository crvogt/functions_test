clc
clear all 
close all

O = [0 0 0];
wX = [1 0 0];
wY = [0 1 0];
wZ = [0 0 1];

C = O;
ptL = [-0.5 0.5 -0.5, 1];
PC = [1 0 0 0;
      0 1 0 0;
      0 0 1 0;
      0 0 0 1];

figure()
hold on;
axis([-3 3, -3 3, -3 3]);
xlabel('x');
ylabel('y');
zlabel('z');

plot3(O(1), O(2), O(3), '.k', 'MarkerSize', 45);
plot3(C(1), C(2), C(3), '*k', 'MarkerSize', 20);
plot3(ptL(1), ptL(2), ptL(3), '.', 'MarkerSize', 30);

hold off;

% lX = [0.71, 0.61, -0.32,0];
% lY = [-0.39, 0.74, 0.53,0];
% lZ = [0.57, -0.25, 0.77,0];
% tran = [0.52, 1.25, -2.53,1];
% 
% % M is our local to world;
% M = [lX;lY;lZ;tran]
lX = [0.71, 0.61, -0.32]';
lY = [-0.39, 0.74, 0.53]';
lZ = [0.57, -0.25, 0.77]';
bot = [0 0 0];
tran = [0.52, 1.25, -2.53,1];
M = [lX lY lZ; bot];
tran = tran';
M = cat(2,M,tran)

% world to local
Minv = inv(M);

ptL = ptL'
M * ptL
Minv * ans

