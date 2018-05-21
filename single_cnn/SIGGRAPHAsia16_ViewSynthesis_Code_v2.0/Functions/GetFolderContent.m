function [imgContentNames, imgContentPaths, imgNumContents, parmContentNames, parmContentPaths, parmNumContents] = GetFolderContent(folderPath)

imgExtension = '.jpg';
parmExtension = '.mat';

%Get the images
listImages = dir([folderPath, '/*', imgExtension]);

imgContentNames = setdiff({listImages.name}, {'.', '..'});
imgNumContents = length(imgContentNames);
imgContentPaths = strcat(strcat(folderPath, '/'), imgContentNames);

%Get the param file associated with each image
listParameters = dir([folderPath, '/*', parmExtension]);

parmContentNames = setdiff({listParameters.name}, {'.', '..'});
parmNumContents = length(parmContentNames);
parmContentPaths = strcat(strcat(folderPath, '/'), parmContentNames);