function numPatches = GetNumPatches()

global param;

height = param.height;
width = param.width;
patchSize = param.patchSize;
stride = param.stride;

numPatchesX = floor((width-patchSize)/stride)+1;
numPatchesY = floor((height-patchSize)/stride)+1;
numPatches = numPatchesY * numPatchesX;
