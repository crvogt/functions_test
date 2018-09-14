function LFDisplayGrid_crv(LF)
    
    nCols = 3;
    nRows = 3;
    distPx = 5;

    figure();
    % Create the subplot
    h = [];
    for iter = 1:(nCols*nRows)
        h(iter) = subplot(nCols,nRows,iter);
        axis off
    end

    % extract the images from the LF
    cX = size(LF,1)/2+1;
    cY = cX;
    pxStart = 5;
    pxEnd = 21;
    pxDist = 8;

    counter = 1
    for iter = pxStart:pxDist:pxEnd
        for jter = pxStart:pxDist:pxEnd

            img = squeeze(LF(iter,jter,:,:,:));
            
            % imshow(uint16(img))
            % pause(2);
            % close all
            image(uint16(img),'Parent',h(counter));
            pause(2)
            counter = counter + 1;
        end
    end
end