% The purpose of this program is to display the sub aperture images pulled from the 
% original lf image. 

function LFDisplayGridAll_crv(LF)
    
    mkdir('/home/carson/libs/gridOutTest');
    % delete('/home/carson/libs/gridOutTest/*.png');
    delete('/home/carson/lightfield_ws/dla/denoising/LFBM5D/testing/basicLF/*.png');
    delete('/home/carson/lightfield_ws/dla/denoising/LFBM5D/testing/denoisedLF/*.png');
    delete('/home/carson/lightfield_ws/dla/denoising/LFBM5D/testing/diffLF/*.png');
    delete('/home/carson/lightfield_ws/dla/denoising/LFBM5D/testing/noisyLF/*.png');
    delete('/home/carson/lightfield_ws/dla/denoising/LFBM5D/testing/sourceLF/*.png');

    nCols = 3;
    nRows = 3;

    gain = 1;
    denoisingOrder = true;

    cX = size(LF,1)/2+1;
    cY = cX;
    % pxStart = 5;
    % pxEnd = 21;
    pxStart = 6;
    pxEnd = 20;
    % pxDist = 8;
    pxDist = (pxEnd-pxStart)/(nCols-1)

    icounter = nRows;
    jcounter = 1;
    if(denoisingOrder)
        for iter = pxEnd:-pxDist:pxStart
            for jter = pxEnd:-pxDist:pxStart
                img = gain * uint16(squeeze(LF(iter,jter,:,:,:)));
                % filename = cat(2,'/home/carson/libs/gridOutTest/CRV_0',int2str(icounter),'_0',int2str(jcounter),'.png');
                filename = cat(2,'/home/carson/lightfield_ws/dla/denoising/LFBM5D/testing/noisyLF/CRV_0',int2str(icounter),'_0',int2str(jcounter),'.png');
                imwrite(img,filename)
                jcounter = jcounter + 1;
            end
            jcounter = 1;
            icounter = icounter - 1;
        end
    else
         for iter = pxStart:pxDist:pxEnd
            for jter = pxStart:pxDist:pxEnd
                img = uint16(squeeze(LF(iter,jter,:,:,:)));
                filename = cat(2,'/home/carson/libs/gridOutTest/CRV_',int2str(iter/pxStart),'_',int2str(jter/pxStart),'.png');
                imwrite(img,filename)
            end
        end
    end
end