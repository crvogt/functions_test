function [pInImgs, pInFeat, pRef, refPos] = ComputeTrainingExamples(curFullLF, curInputLF, fullLFPoses, inputLFPoses)

global param;

% cropSize = param.cropSizeTraining;
numRefs = param.numRefs; %Will need to check on this
patchSize = param.patchSize;
stride = param.stride;

%curFullLF h, w, 5 (rgbtp)
%%%%%%%%%%%%% preparing input images %%%%%%%%%%%%%%%
[height, width, ~] = size(curInputLF);

% These are input images, reorganized to h, w, 12
% pInImgs patches look like 40, 40, 15, 1064
% They keep the same rgbtp values, but are split now
pInImgs = GetPatches(curInputLF, patchSize, stride);

%%%%%%%%%%%%% selecting random references %%%%%%%%%%
[~, ~, numImgs] = size(curFullLF);
numImgs = numImgs/5;
numSeq = randperm(numImgs); %This will be randperm(sizeofinternal vals)
refInds = numSeq(1:numRefs);%Inds being indices

%%%%%%%%%%%%% initializing the arrays %%%%%%%%%%%%%%
numPatches = GetNumPatches();

pInFeat = zeros(patchSize, patchSize, param.numDepthFeatureChannels, numPatches * numRefs);
fprintf('\npinfeat\n');
size(pInFeat)

pRef = zeros(patchSize, patchSize, 3, numPatches * numRefs);
refPos = zeros(2, numPatches * numRefs);

% figure(1)
% hold on;
for ri = 1 : numRefs
    
    fprintf('Working on random reference %d of %d: ', ri, numRefs);
    % these are any four images from the lf... thoughh not sure if patches or whole images

    % Theta is x, phi is y    
    wInds = (ri-1) * numPatches + 1 : ri * numPatches;
    
    ref = curFullLF(:, :, (((refInds(ri) - 1) * 5) + 1):(((refInds(ri) - 1) * 5) + 5));
    pRef = GetPatches(ref, patchSize, stride);
     % fprintf('\npRef size:\n'); 40 40 5 1064

    inputView.Phi(1) = inputLFPoses(1,2,1);
    inputView.Phi(2) = inputLFPoses(1,2,2);
    inputView.Phi(3) = inputLFPoses(1,2,3);
    inputView.Theta(1) = inputLFPoses(1,1,1);
    inputView.Theta(2) = inputLFPoses(1,1,2);
    inputView.Theta(3) = inputLFPoses(1,1,3);
    inputView.Phi = inputView.Phi';
    inputView.Theta = inputView.Theta';

    curRefPos.Phi = fullLFPoses(1, 2, refInds(ri));
    curRefPos.Theta = fullLFPoses(1, 1, refInds(ri));

    deltaViewPhi = inputView.Phi - curRefPos.Phi; 
    deltaViewTheta = inputView.Theta - curRefPos.Theta;

    inFeat = PrepareDepthFeatures(curInputLF, deltaViewPhi, deltaViewTheta);
    % inFeat = CropImg(inFeat, cropSize);
    % pInFeat(:, :, :, wInds) = GetPatches(inFeat, patchSize, stride);
    pInFeat = GetPatches(inFeat, patchSize, stride);
    
    %%%%%%%%%%%%%%%%%%%%%% preparing ref positions %%%%%%%%%%%%%%%%%%%
    % refPos(1, wInds) = repmat(curRefPos.Y, [1, numPatches]);
    % refPos(2, wInds) = repmat(curRefPos.X, [1, numPatches]);
    
    %% Plot some shit, to visualize
    % plot(inputView.Theta, inputView.Phi, '.k', 'MarkerSize', 30);
    % plot(curRefPos.Theta, curRefPos.Phi, '*b', 'MarkerSize', 20);
    % pause(3)

    fprintf(repmat('\b', 1, 5));
    fprintf('Done\n');
end
% hold off;


