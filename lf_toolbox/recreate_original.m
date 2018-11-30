subAPDir = '/home/carson/libs/raytrix_gp_data/raytrixImages/enhanced_light/0'

pxStart = 6;
pxEnd = 20;
pxDist = 1;
nCols = pxEnd - pxStart;
nRows = nCols;

icounter = 1;
jcounter = 1;

for iter = pxStart:pxDist:pxEnd
    for jter = pxStart:pxDist:pxEnd
        if icounter < 10 && jcounter < 10
            filename = cat(2, writeDir, '/CRV_0',int2str(icounter),'_0',int2str(jcounter),'.png');
        elseif icounter > 9 && jcounter > 9
            filename = cat(2, writeDir, '/CRV_',int2str(icounter),'_',int2str(jcounter),'.png');
        elseif icounter > 9 && jcounter < 10
            filename = cat(2, writeDir, '/CRV_',int2str(icounter),'_0',int2str(jcounter),'.png');
        else
            filename = cat(2, writeDir, '/CRV_0',int2str(icounter),'_',int2str(jcounter),'.png');
        end
        
        jcounter = jcounter + 1;
    end
    icounter = icounter + 1;
    jcounter = 1;
end