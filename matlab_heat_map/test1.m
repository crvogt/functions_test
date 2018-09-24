clc
clear all
close all

pathToData = '/home/carson/libs/raytrix_data/light_test_1/psnrData.txt';
A = importdata(pathToData);

A(87,4) = 31;

tl1 = table(A(1:20,2),A(1:20,3),A(1:20,4));
tl1.Properties.VariableNames{'Var1'} = 'Gain';
tl1.Properties.VariableNames{'Var2'} = 'Shutter_Speed';
tl2 = table(A(21:40,2),A(21:40,3),A(21:40,4));
tl2.Properties.VariableNames{'Var1'} = 'Gain';
tl2.Properties.VariableNames{'Var2'} = 'Shutter_Speed';
tl3 = table(A(41:60,2),A(41:60,3),A(41:60,4));
tl3.Properties.VariableNames{'Var1'} = 'Gain';
tl3.Properties.VariableNames{'Var2'} = 'Shutter_Speed';
tl4 = table(A(61:80,2),A(61:80,3),A(61:80,4));
tl4.Properties.VariableNames{'Var1'} = 'Gain';
tl4.Properties.VariableNames{'Var2'} = 'Shutter_Speed';
tl5 = table(A(81:100,2),A(81:100,3),A(81:100,4));
tl5.Properties.VariableNames{'Var1'} = 'Gain';
tl5.Properties.VariableNames{'Var2'} = 'Shutter_Speed';

figure
subplot(5,1,5);
subplot(5,1,1)
h(1) = heatmap(tl1,'Gain', 'Shutter_Speed', 'ColorVariable','Var3','ColorLimits',[-30 30], 'Colormap',autumn)
title(h(1), 'PSNR at Light Setting 1')
h(1).ColorbarVisible = 'off'
subplot(5,1,2)
h(2) = heatmap(tl2,'Gain', 'Shutter_Speed', 'ColorVariable', 'Var3')
title(h(2), 'PSNR at Light Setting 2')
h(2).ColorbarVisible = 'off'
subplot(5,1,3)
h(3) = heatmap(tl3,'Gain', 'Shutter_Speed', 'ColorVariable', 'Var3')
title(h(3), 'PSNR at Light Setting 3')
h(3).ColorbarVisible = 'off'
subplot(5,1,4)
h(4) = heatmap(tl4,'Gain', 'Shutter_Speed', 'ColorVariable', 'Var3')
title(h(4), 'PSNR at Light Setting 4')
h(4).ColorbarVisible = 'off'
subplot(5,1,5)
h(5) = heatmap(tl5,'Gain', 'Shutter_Speed', 'ColorVariable', 'Var3')
title(h(5), 'PSNR at Light Setting 5')
h(5).ColorbarVisible = 'off'