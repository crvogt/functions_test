clc
close all
clear all

addpath('../matlab');

filename = '/media/carson/WDPassport/deep_learn/pr2_dataset/set_1/Trimpr2VSphere1.txt';

pose = importdata(filename);

subj = [0.7 -0.3 (0.71+0.05+0.0125)];

radius = 1.15 - subj(3);

figure(1)
hold on;
axis equal
plot3(pose(:,1), pose(:,2), pose(:,3), '*k', 'MarkerSize', 10);
hold off;

% subtract subj
pose = pose - subj;
subj = subj - subj;
figure(2)
hold on;
plot3(pose(:,1), pose(:,2), pose(:,3), '*k', 'MarkerSize', 10);
plot3(subj(1), subj(2), subj(3), '*b', 'MarkerSize', 15);
hold off;