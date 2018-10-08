% The purpose of this program is to display the sub aperture images pulled from the 
% original lf image. 

function LFDisplayGridAll_crv(LF)
    
    mkdir('/home/carson/libs/gridOutTest');

    nCols = 17;
    nRows = 17;

    cX = size(LF,1)/2+1;
    cY = cX;
    pxStart = 5;
    pxEnd = 21;
    pxDist = 1;

    counter = 1;
    for iter = pxStart:pxDist:pxEnd
        for jter = pxStart:pxDist:pxEnd
            img = uint16(squeeze(LF(iter,jter,:,:,:)));
            filename = cat(2,'/home/carson/libs/gridOutTest/',int2str(iter),'_',int2str(jter),'.png');
            imwrite(img,filename)
        end
    end
end