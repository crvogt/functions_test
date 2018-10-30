% The purpose of this program is to display the sub aperture images pulled from the 
% original lf image. 

function LFWriteOutDepthSAI_crv(LF)
    
%    mkdir('/home/carson/libs/SAI_output');
    delete('/home/carson/libs/SAI_output/scene_1/l1/*.png');
    writeDir = '/home/carson/libs/SAI_output/scene_1/l1/';


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
            if icounter < 10 && jcounter < 10
                filename = cat(2, writeDir, 'CRV_0',int2str(icounter),'_0',int2str(jcounter),'.png');
            elseif icounter > 9 && jcounter > 9
                filename = cat(2, writeDir, 'CRV_',int2str(icounter),'_',int2str(jcounter),'.png');
            elseif icounter > 9 && jcounter < 10
                filename = cat(2, writeDir, 'CRV_',int2str(icounter),'_0',int2str(jcounter),'.png');
            else
                filename = cat(2, writeDir, 'CRV_0',int2str(icounter),'_',int2str(jcounter),'.png');
            end
            
            imwrite(img,filename)
            jcounter = jcounter + 1;
        end
        icounter = icounter + 1;
        jcounter = 1;
    end

end
