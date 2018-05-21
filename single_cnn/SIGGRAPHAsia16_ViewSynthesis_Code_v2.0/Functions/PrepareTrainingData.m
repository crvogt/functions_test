function PrepareTrainingData()

global param;

fprintf('\nSecond\n');

listSets = dir(param.baseTrainFolder);
trainingSets = setdiff({listSets.name}, {'.', '..'});

fprintf('\nSize of trainingSets\n');
trainingSets = trainingSets';

outputFolder = param.baseTrainFolder;
MakeDir([outputFolder, 'test_output_dir']);

numScenes = length(trainingSets);
numPatches = GetNumPatches();
numTotalPatches = numPatches * param.numRefs * numScenes;
writeOrder = randperm(numTotalPatches);
firstBatch = true;

% Each training set will be considered a scene
% Still need to think about randomizing the way in which the data is fed into the network
% This could be taken care of by writeOrder, below
for iter = 1%:numScenes
    sceneInternalFolder = strcat(param.baseTrainFolder, '/train_set_', num2str(iter), '/internal_points');
    sceneVertexFolder = strcat(param.baseTrainFolder, '/train_set_', num2str(iter), '/vertices');

    % For internal points
    [imgContNames, imgContPaths, imgNumConts, parmContNames, parmContPaths, parmNumConts] ...
        = GetFolderContent(sceneInternalFolder);

    % parmContNames(1){'5470_-0_8253887_1_081807.mat'}
    fprintf('\nGetting fullLF values...\n');
    curFullLF = ReadLightFieldImages(imgContPaths, parmContPaths);
    fullLFPoses = GetLFPoses(parmContNames);

    % For vertices alone
    [imgContNames, imgContPaths, imgNumConts, parmContNames, parmContPaths, parmNumConts] ...
        = GetFolderContent(sceneVertexFolder);

    fprintf('\nGetting inputLF values...\n');
    curInputLF = ReadLightFieldImages(imgContPaths, parmContPaths);
    inputLFPoses = GetLFPoses(parmContNames);
    size(curInputLF)

    % Add the vertex values to the full light field
    fprintf('\nAdding inputLF to fullLF values...\n');
    curFullLF = cat(3, curInputLF, curFullLF);
    fullLFPoses = cat(3, inputLFPoses, fullLFPoses);

    % pause(100);
    
    fprintf('\nPreparing training examples\n');
    fprintf('------------------------------\n');
    % pause(5);
    [pInImgs, pInFeat, pRef, refPos] = ComputeTrainingExamples(curFullLF, curInputLF, fullLFPoses, inputLFPoses);
    fprintf('\nFinished preparing training examples\n');
    pause(3);

    fprintf('\nWriting training examples\n\n');
    firstBatch = WriteTrainingExamples(pInImgs, pInFeat, pRef, refPos, outputFolder, writeOrder, (iter-1) * numPatches * param.numRefs + 1, firstBatch, numTotalPatches);
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

end