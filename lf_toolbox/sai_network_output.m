clc
clear all
close all

% Iterate through the scenes:
baseDir = '/home/carson/libs/SAI_output/Experiment1';
list = dir([baseDir, '/*']);

list([list.isdir] == 0)=[];

contNames = setdiff({list.name}, {'.', '..'});

for iter=1:2%length(contNames)
    % Find all Processed Images
    curDir = strcat(baseDir, '/', contNames{iter});
    % Getting all processed images
    curDirList = dir([curDir, '/*_Processed.png']);
    curDirNames = {curDirList.name};
    curDirNames = sort(curDirNames);
    
    % Create directories based on the number of shutter levels
    for lightLevel = 1:length(curDirList)
       folderName = strcat(curDir, '/level_', num2str(lightLevel));
       [mkdirSuccess, ~, ~] = mkdir(folderName);
       if mkdirSuccess
           fprintf('successfully created %s\n', folderName);
           imgName = strcat(curDir, '/', curDirNames(lightLevel));
           getSais(imgName, folderName);
       else
           fprintf('there was an error creating %s\n', folderName);
       end
    end
    fprintf('\n');  
end

