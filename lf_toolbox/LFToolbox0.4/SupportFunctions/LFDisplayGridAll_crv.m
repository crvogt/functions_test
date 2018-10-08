% The purpose of this program is to display the sub aperture images pulled from the 
% original lf image. 

function LFDisplayGridAll_crv(LF)
    
    nCols = 17;
    nRows = 17;

    figure();
    % hold on;
    % Create the subplot
    h = [];
    for iter = 1:(nCols*nRows)
        h(iter) = subplot(nCols,nRows,iter);
        % axis off
        % set(gca,'xtick',[],'ytick',[])
    end
    % hold off;
    % extract the images from the LF
    % This chooses specific directional images to pull
    % from, resulting in the images from different angles
    cX = size(LF,1)/2+1;
    cY = cX;
    pxStart = 5;
    pxEnd = 21;
    pxDist = 1;
    hold on;
    counter = 1;
    for iter = pxStart:pxDist:pxEnd
        for jter = pxStart:pxDist:pxEnd
            img = squeeze(LF(iter,jter,:,:,:));
            image(uint16(img),'Parent',h(counter));
            axis off
            set(gca,'xtick',[],'ytick',[])
            % pause(0.5);
            counter = counter + 1;
        end
    end
    hold off;
end