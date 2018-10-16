% The purpose of this program is to display the sub aperture images pulled from the 
% original lf image. 

function subApGrid = LFReturnGrid_crv(LF)
    
    nCols = 3;
    nRows = 3;
    distPx = 5;

    % figure();
    % Create the subplot
    % h = [];
    % for iter = 1:(nCols*nRows)
        % h(iter) = subplot(nCols,nRows,iter);
        % axis off
    % end

    % extract the images from the LF
    % This chooses specific directional images to pull
    % from, resulting in the images from different angles
    cX = size(LF,1)/2+1;
    cY = cX;
    pxStart = 5;
    pxEnd = 21;
    pxDist = 8;

    subApGrid = zeros(size(LF,3),size(LF,4),size(LF,5), nCols,nRows);

    counter = 1;
    iterCount = 1;
    jterCount = 1;
    for iter = pxStart:pxDist:pxEnd
        for jter = pxStart:pxDist:pxEnd
            img = squeeze(LF(iter,jter,:,:,:));
            % image(uint16(img),'Parent',h(counter));
            subApGrid(:,:,:,iterCount,jterCount) = img;
            counter = counter + 1;
            jterCount = jterCount + 1;
        end
        iterCount = iterCount + 1;
        jterCount = 1;
    end
end