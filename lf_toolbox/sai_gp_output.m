clc
clear all
close all

% Iterate through the scenes:
baseDir = '/home/carson/libs/raytrix_gp_data/raytrixImages/low_light';
list = dir([baseDir, '/*']);

list([list.isdir] == 1)=[];

contNames = setdiff({list.name}, {'.', '..'});

for iter=1:length(contNames)   
    % Create directories based on the number of shutter levels
    imgName = strcat(baseDir, '/', contNames{iter});
%     imshow(imgName)
%     pause(100)
    newDir = split(contNames{iter}, '.');
    newDir = newDir{1};
    folderName = strcat(baseDir, '/', newDir);
    pause(2)
    [mkdirSuccess, ~, ~] = mkdir(folderName);
    if mkdirSuccess
        fprintf('successfully created %s\n', folderName);
        fprintf('imgName %s\n', imgName);
        get_sais(imgName, folderName);
    else
        fprintf('there was an error creating %s\n', folderName);
    end
    fprintf('\n');  
end
