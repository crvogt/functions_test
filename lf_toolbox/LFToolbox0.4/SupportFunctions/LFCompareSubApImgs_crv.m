% The purpose of this program is to display the sub aperture images pulled from the 
% original lf image. 

function LFCompareSubApImgs_crv(LF)
    
    nCols = 3;
    nRows = 3;
    distPx = 5;

    % figure(1);
    % hold on;
    % Create the subplot
    imgSP = [];
    diffSP = [];
    for iter = 1:(nCols*nRows)
        % imgSP(iter) = subplot(nCols,nRows,iter);
        diffSP(iter) = subplot(nCols,nRows,iter);
        axis off
    end

    % Get center image
    % centImg = squeeze(LF(round(end/2),round(end/2),:,:,:));
    centImg = squeeze(LF(13,13,:,:,:));

    imgArray = zeros(101,101,3,nCols*nRows);

    % extract the images from the LF
    % This chooses specific directional images to pull
    % from, resulting in the images from different angles
    cX = size(LF,1)/2+1;
    cY = cX;
    pxStart = 5;
    pxEnd = 21;
    pxDist = 8;

    counter = 1
    for iter = pxStart:pxDist:pxEnd
        for jter = pxStart:pxDist:pxEnd
            img = squeeze(LF(iter,jter,:,:,:));
            % image(uint16(img),'Parent',imgSP(counter));
            % pause(1)
            imgArray(:,:,:,counter) = img;
            counter = counter + 1;
        end
    end

    for iter = 1:(nRows*nCols)
        imgArray(:,:,:,iter) = imabsdiff(imgArray(:,:,:,iter),centImg);
    end


    figure(2)
    fprintf('In fig\n');
    % hold on
    for iter = 1:(nCols*nRows)
        image(uint16(imgArray(:,:,:,iter)),'Parent',diffSP(iter));
    end
    % hold off;
    % image(uint16(centImg))
end