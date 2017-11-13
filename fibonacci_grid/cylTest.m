maxR = 0.5;
area = 2 * pi * maxR * maxR;
pointDensity = 500;

ng = area * pointDensity;

hp = maxR / (2 * pi * maxR);
wp = 1;

if(hp*wp > ng)
    pointsfound = 10000000;
    while(pointsfound > ng)
       tempPoints = pointsfound;
       tempHP = hp;
       tempWP = wp;
       pointsfound = hp * wp;
       hp = hp * 0.999;
       wp = wp * 0.999;
    end
    
    differenceTemp = abs(tempHP * tempWP - ng)
    difference = abs(hp * wp - ng);
    
    if(differenceTemp < difference)
        hp = tempHP;
        wp = tempWP;
    end

elseif(hp * wp < ng)
    pointsfound = 0;
    while(pointsfound < ng)
        tempPoints = pointsfound;
        tempHP = hp;
        tempWP = wp;
        pointsfound = hp * wp;
        hp = hp * 1.001;
        wp = wp * 1.001;
    end
    differenceTemp = abs(tempHP * tempWP - ng);
    difference = abs(hp * wp - ng);
    
    if(differenceTemp < difference)
        hp = tempHP;
        wp = tempWP;
    end
end

figure(1)
hold on;
axis([-0.5 0.5 -0.5 0.5 -0.5 0.5])

zStep = maxR / hp;
yStep = (2 * pi) / wp;
angleCount = 0;
valZ = 0;
while(valZ <= 0.3)
    while(angleCount <= (2*pi))
        valY = maxR * sin(angleCount);
        valX = maxR * cos(angleCount);
        angleCount = angleCount + yStep;
        plot3(valX, valY, valZ, '*', 'MarkerSize',10)
    end
    angleCount = 0;
    valZ = valZ + zStep;
end

hold off;


