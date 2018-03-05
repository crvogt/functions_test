clc
clear all
close all

phase = 0.1;
frequency = 2;
amplitude = 1;
frequency2 = 3;
frequency3 = 3.5;

theta = 0;
sampleFreq = 0.001;
cpsSampFreq = 0.01;
cps = 2;
% subplot 212

t = 0:sampleFreq:6;
tNum = 0:length(t)-1;
y3 = amplitude*cos(2*frequency3*pi*t) + amplitude;
y2 = amplitude*cos(2*frequency2*pi*t) + amplitude;
y1 = amplitude*sin(2*frequency*pi*t) + amplitude;
y = y1 + y2;% + y3;

r = y; 

%  Now need cycles per second
% lets say 0.5
% cps = 0.5;
% where x is seconds

p1 = subplot(2,2,1);
hold on;
% axis([0 5 0 3])
title('Signal');
plot(t,y, 'k')
hold off;

pause(2)

maxCPS = 5;
% cpsSampFreq = sampleFreq;
% Interesting, change this sample freq relative to other
for cps = 0:cpsSampFreq:maxCPS
    
    theta = 2*pi*sampleFreq*tNum*cps;

    xT = r.*cos(theta);
    yT = r.*sin(theta); 

    p2 = subplot(2,2,2);
    hold on
    axis([-6 6 -6 6])
    plot(xT, yT)
    hold off
    pause(0.1)
    if(cps ~= maxCPS)
        cla(p2)
    end
    avgY = sum(yT)/length(yT);
    p3 = subplot(2,2,[3 4]);
    hold on;
    axis([-0.5 maxCPS 0 3])
    plot(cps, avgY,'*k')
    hold off;
end



% subplot(2,2,3)
% hold on
% title('Polar Plot');
% polarplot(theta, r);
% hold off






% subplot 212
