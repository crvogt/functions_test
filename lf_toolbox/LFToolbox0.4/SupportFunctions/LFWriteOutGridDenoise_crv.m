% The purpose of this program is to display the sub aperture images pulled from the 
% original lf image. 

function LFWriteOutGridDenoise_crv(LFBright, LFDim, maxNum)
    
    mkdir('/home/carson/libs/gridOutTest');
    % delete('/home/carson/libs/gridOutTest/*.png');
    delete('/home/carson/lightfield_ws/dla/denoising/LFBM5D/testing/basicLF/*.png');
    delete('/home/carson/lightfield_ws/dla/denoising/LFBM5D/testing/denoisedLF/*.png');
    delete('/home/carson/lightfield_ws/dla/denoising/LFBM5D/testing/diffLF/*.png');
    delete('/home/carson/lightfield_ws/dla/denoising/LFBM5D/testing/noisyLF/*.png');
    delete('/home/carson/lightfield_ws/dla/denoising/LFBM5D/testing/sourceLF/*.png');

    denoisingOrder = true;
    if ~maxNum
        nCols = 3;
        nRows = 3;    
        cX = size(LFDim,1)/2+1;
        cY = cX;
        % pxStart = 5;
        % pxEnd = 21;
        pxStart = 6;
        pxEnd = 20;
        % pxDist = 8;
        pxDist = (pxEnd-pxStart)/(nCols-1)
    else 
        pxStart = 6;
        pxEnd = 20;
        pxDist = 1;
        nCols = pxEnd - pxStart;
        nRows = nCols;
    end

    icounter = nRows + 1;
    jcounter = 1;
    if(denoisingOrder)
        for iter = pxEnd:-pxDist:pxStart
            for jter = pxEnd:-pxDist:pxStart
                % get the reference image
                imgRef = uint16(squeeze(LFBright(iter,jter,:,:,:)));
                imgRefHSV = rgb2hsv(imgRef);
                % get the average for the intensity values
                meanRefV = mean(mean(imgRefHSV(:,:,3)));
                % Get the image of interest
                img = uint16(squeeze(LFDim(iter,jter,:,:,:)));
                imgHSV = rgb2hsv(img);
                % Get the mean of ioi intensity
                meanV = mean(mean(imgHSV(:,:,3)));
                % meanRefV = gain *meanV
                gain = meanRefV/meanV; 
                imgHSV(:,:,3) = gain * imgHSV(:,:,3);
                imgHSV(:,:,3) = histeq(imgHSV(:,:,3));
                imgWithGain = hsv2rgb(imgHSV);

                % filename = cat(2,'/home/carson/libs/gridOutTest/CRV_0',int2str(icounter),'_0',int2str(jcounter),'.png');
                if icounter > 9 && jcounter < 10
                    filename = cat(2,'/home/carson/lightfield_ws/dla/denoising/LFBM5D/testing/noisyLF/CRV_',int2str(icounter),'_0',int2str(jcounter),'.png');
                elseif icounter < 10 && jcounter > 9
                    filename = cat(2,'/home/carson/lightfield_ws/dla/denoising/LFBM5D/testing/noisyLF/CRV_0',int2str(icounter),'_',int2str(jcounter),'.png');
                elseif icounter > 9 && jcounter > 9
                    filename = cat(2,'/home/carson/lightfield_ws/dla/denoising/LFBM5D/testing/noisyLF/CRV_',int2str(icounter),'_',int2str(jcounter),'.png');
                else 
                    filename = cat(2,'/home/carson/lightfield_ws/dla/denoising/LFBM5D/testing/noisyLF/CRV_0',int2str(icounter),'_0',int2str(jcounter),'.png');
                end 

                imwrite(imgWithGain,filename);
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