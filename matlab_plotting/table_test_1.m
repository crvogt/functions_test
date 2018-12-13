clc
close all
clear all

f = '/home/carson/libs/raytrix_gp_data/raytrixImages/high_light_raw'

f0 = strcat(f, '/0.png');
src0 = imread(f0);
f1 = strcat(f, '/1.png');
src1 = imread(f1);

f = figure;
uit = uitable(f,'Data',src0,'Position',[20 20 262 204]);

% pic = fullfile(matlabroot, 'toolbox', 'image', 'icon', 'icon_info.png');
% uitable('Data', {[src0]})

% T = table(src0, src1);

% TString = evalc('disp(T)');

% annotation(gcf, 'Textbox', TString)

% dinfo = dir('/home/carson/libs/raytrix_gp_data/raytrixImages/high_light_raw/*.png');

% Set up an example table.
% num_imgs = numel(dinfo); %numel is safer than length
% T = table(cell(1, num_imgs), 'VariableNames', {'image'}, 'RowNames', {'row name'});
% for K = 1 : numimage




% dinfo = dir('*.jpg');
% T = table();
% for K = 1 : length(dinfo)
% filename = dinfo(K).name;
% filecontent = imread(filename);
% T{filename,1} = filecontent;
% end