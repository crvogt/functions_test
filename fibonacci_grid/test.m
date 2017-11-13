clc
clear all 
close all

counter = 0;

xC = 0.1;
yC = 0.1;

zMax = 0.10;

al = 0.01;

R = zMax;
r = 0;

C = 0;
z = zMax - 0.00001;

figure(1)
hold on;

while(z >= 0)
    r = sqrt(R^2 - z^2)
    CI = (2 * pi * al) / (2*pi*R);
    
    while(C < 2*pi)

        C = C + CI;

        x = r * cos(C);
        y = r * sin(C);

        %x = x + xC;
        %y = y + yC;

        plot3(x, y, z, '*', 'MarkerSize', 10)
        axis([-0.5 0.5 -0.5 0.5, -0.5, 0.5])
        grid on;

        counter = counter + 1;


    end
    C = 0;
    z = z - 0.01
end

counter

hold off;

density = counter;

%Now for a planar surface
depth = 0;

lengthMin = 0;
lengthMax = 2 * pi * R;
heightMin = 0;
heightMax = zMax;

intervalArea = 0;