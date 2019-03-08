% The purpose of this program is to display the sub aperture images pulled from the 
% original lf image. 

function LFWriteOutDepthSAI_crv(LF, writeDir)
    delete(strcat(writeDir, '/*.png'));

    pxStart = 6;
    pxEnd = 20;
    pxDist = 1;
    nCols = pxEnd - pxStart;
    nRows = nCols;

    icounter = 1;
    jcounter = 1;

    for iter = pxStart:pxDist:pxEnd
        for jter = pxStart:pxDist:pxEnd
            img = uint16(squeeze(LF(iter,jter,:,:,:)));
            % img = uint8(squeeze(LF(iter, jter, :, :, :)));
            if icounter < 10 && jcounter < 10
                filename = cat(2, writeDir, '/CRV_0',int2str(icounter),'_0',int2str(jcounter),'.png');
            elseif icounter > 9 && jcounter > 9
                filename = cat(2, writeDir, '/CRV_',int2str(icounter),'_',int2str(jcounter),'.png');
            elseif icounter > 9 && jcounter < 10
                filename = cat(2, writeDir, '/CRV_',int2str(icounter),'_0',int2str(jcounter),'.png');
            else
                filename = cat(2, writeDir, '/CRV_0',int2str(icounter),'_',int2str(jcounter),'.png');
            end
            
            img = imresize(img(1:100, 1:100, :), [200 NaN]);
            % imwrite(img(1:100,1:100,:), filename)
            imwrite(img, filename);
            jcounter = jcounter + 1;
        end
        icounter = icounter + 1;
        jcounter = 1;
    end
end
