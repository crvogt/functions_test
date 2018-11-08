clc
clear all
close all

% Iterate through the scenes:
baseDir = '/home/carson/libs/SAI_output';
list = dir([baseDir, '/*'])
length(list)
for iter=1:length(list)
	if list(iter).isdir
		list(iter) = [];
		iter = 1;
	end
end
contNames = setdiff({list.name}, {'.', '..'});
contNames
for iter=1:length(contNames)
	fprintf('%s\n', contNames{iter})
end

% Iterate through the different exposures:

