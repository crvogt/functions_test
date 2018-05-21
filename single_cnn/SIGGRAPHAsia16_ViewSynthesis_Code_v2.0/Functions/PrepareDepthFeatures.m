function featuresStack = PrepareDepthFeatures(inputLF, deltaPhi, deltaTheta)

global param;
depthResolution = param.depthResolution;
deltaDisparity = param.deltaDisparity;

%%% convert the input rgb light field to grayscale
% [height, width, ~, angHeight, angWidth] = size(inputLF);
[height, width, imgNum] = size(inputLF);
% imgNum = imgNum / 5;
grayLF = zeros(height, width, imgNum/5);
fprintf('\ngrayLF size:\n');
size(grayLF)
% pause(50);
grayCount = 1;

for iter = 1:5:imgNum
   grayLF(:, :, grayCount) = rgb2gray(inputLF(:, :, iter:(iter+2))); 
   % imshow(grayLF(:,:,grayCount));
   % pause(5);
   grayCount = grayCount + 1;
end

defocusStack = zeros(height, width, depthResolution);
correspStack = zeros(height, width, depthResolution);
featuresStack = zeros(height, width, 200, 'single');

delta = 2 * deltaDisparity / (depthResolution - 1);

indDepth = 1;
count = 0;
% testDepth = -deltaDisparity:delta:deltaDisparity
% size(testDepth)
% pause(100)
% figure(1)
% hold on;
X = zeros(height, width);
Y = zeros(height, width);

% for curDepth = -deltaDisparity:delta:deltaDisparity
for curDepth = -20:4:20
    curDepth
    if (mod(indDepth, 5) == 0)
        fprintf(repmat('\b', [1, count]));
    end
    
    shearedLF = zeros(height, width, imgNum);

    % THIS IS WHERE THE PIXEL VALUES ARE STORED
    % [X, Y] = meshgrid(1:width, 1:height);
    % fprintf('\nSize of Y and X\n');
    % size(Y)
    % size(X)
    % fprintf('\nSize of curDepth:\n')
    % size(curDepth)

    % pause(15);
    
    %%% backward warping all the input images using each depth level (see
    %%% Eq. 5)
    
    for indView = 1:(imgNum/5)
        % time1 = tic;
        ilfStart = (indView * 4) + (indView - 1);
        X = inputLF(:,:,ilfStart); % This should give us the theta values
        Y = inputLF(:,:,(ilfStart+1)); % This should give us the phi values
        % time2 = tic;
        % fprintf('\nTime taken for X and Y %f\n', (time2 - time1)*10^-6)
        % if indView == 1
        %     plot(X, Y, '.k');
        % elseif indView == 2
        %     plot(X, Y, '.b');
        % elseif indView == 3
        %     plot(X, Y, '.r');
        % end
        % pause(2);
        % time1 = tic;
        curX = X + deltaTheta(indView) * curDepth;
        curY = Y + deltaPhi(indView) * curDepth;
        % time2 = tic;
        % fprintf('\nTime taken for curVals %f\n', (time2 - time1)*10^-6)

        % if indView == 1
        %     plot(curX, curY, '.k');
        % elseif indView == 2
        %     plot(curX, curY, '.b');
        % elseif indView == 3
        %     plot(curX, curY, '.r');
        % end
        % pause(0.5);

        % shearedLF(:, :, indView) = interp2(X, Y, grayLF(:, :, indView), curX, curY, 'cubic', nan);
        % fprintf('\nindView %d\n', indView); 
        % size(grayLF)
        % size(X)
        % size(Y)
        % size(curX)
        % size(curY)
        time1 = tic;
        fprintf('\nshowing grayLF\n');
        imshow(grayLF(:,:,indView));
        pause(5)
        shearedLF(:, :, indView) = griddata(X, Y, grayLF(:,:,indView), curX, curY, 'cubic');
        fprintf('\nshowing shearedLF\n');
        imshow(shearedLF(:,:,indView))
        grayLF(1,1,indView)
        shearedLF(1,1,indView)
        pause(100)
        time2 = tic;
        fprintf('\nTime taken for shearedLF %f\n', (time2 - time1)*10^-6)
    end
    
    % fprintf('\nDone with shearedLF generation\n');

    % pause(100);

    %%% computing the final mean and variance features for each depth level
    %%% using Eq. 6 
    defocusStack(:, :, indDepth) = DefocusResponse(shearedLF);
    correspStack(:, :, indDepth) = CorrespResponse(shearedLF);
    
    if (mod(indDepth, 10) == 0)
        count = fprintf('%d %%', indDepth/depthResolution*100);
    end
    
    indDepth = indDepth + 1;
    
end
% hold off;
fprintf('\nExited main loop, now adding to featuresStack...\n');

featuresStack(:, :, 1:100) = single(defocusStack);
featuresStack(:, :, 101:200) = single(correspStack);
fprintf('\nDone preparing depth feautres\n');
% pause(100);