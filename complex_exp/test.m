clc
clear all
close all

% figure(1)
% grid on;
% hold on;
% 
% arLocX = 0;
% arLocY = 0;
% 
% spX = 0;
% spY = 1;
% 
% yaw = pi/1.2;
% hComp = complex(cos(yaw),sin(yaw));
% hComp2 = complex(spX, spY);
% hComp2 = hComp2/abs(hComp2);
% 
% plot(arLocX, arLocY, '-s')
% plot(spX, spY, 'x')
% plot(real(hComp), imag(hComp), '*');
% plot(real(hComp2), imag(hComp2), 'diamond')
% axis([-4 4 -4 4])
% hold off;
% 
% figure(2)
% grid on;
% hold on;
% 
% newYaw = 2*pi - pi/1.2;
% rotateBy = complex(cos(newYaw), sin(newYaw));
% 
% testHR =     complex((real(hComp)*real(rotateBy)-imag(hComp)*imag(rotateBy)),(real(hComp)*imag(rotateBy)+imag(hComp)*real(rotateBy))) 
% testNewSPH = complex((real(hComp2)*real(rotateBy)-imag(rotateBy)*imag(hComp2)),(real(hComp2)*imag(rotateBy)+imag(hComp2)*real(rotateBy)))
% 
% plot(arLocX, arLocY, '-s')
% plot(real(testHR),imag(testHR), '*')
% plot(real(testNewSPH),imag(testNewSPH),'diamond')
% axis([-4 4 -4 4])
% 
% hold off;
% 
% figure(3)
% hold on;
% grid on;
% 
% spX = 3;
% spY = 3;
% 
% locX = 1;
% locY = 3;
% % rotate by 90
% dirComp = complex((spX - locX), (spY - locY));
% dirComp2 = complex(-imag(dirComp), -real(dirComp));
% plot(real(dirComp),imag(dirComp),'diamond')
% plot(real(dirComp2), imag(dirComp2), 'x')
% plot(0,0,'o')
% axis([-4 4 -4 4])
% 
% hold off;

% figure(4)
% hold on;
% grid on;
% 
% spX = 3;
% spY = 3;
% 
% locX = 1;
% locY = 3;
% % rotate about a point by 90
% dirComp = complex((spX - locX), (spY - locY));
% dirComp2 = complex(-imag(dirComp) + 2, -real(dirComp));
% plot(real(dirComp),imag(dirComp),'diamond')
% plot(real(dirComp2), imag(dirComp2), 'x')
% plot(0,0,'o')
% axis([-4 4 -4 4])
% 
% hold off;

figure(4)
hold on;
grid on;

spX = 2;
spY = 3;

locX = 1;
locY = 1;

% zero out
offsetX = locX;
offsetY = locY;

locX = locX - offsetX;
locY = locY - offsetY;
spX = spX - offsetX;
spY = spY - offsetY;

%plot  
plot(spX, spY,'diamond')
plot(locX, locY, 'x')
plot(0,0,'o')
axis([-4 4 -4 4])

% now rotate
rotateYaw = -pi/2;
rotateBy = complex(cos(rotateYaw), sin(rotateYaw));
spComplex = complex((spX*real(rotateBy)-spY*imag(rotateBy)),(spX*imag(rotateBy)+spY*real(rotateBy)));
plot(real(spComplex), imag(spComplex), 'diamond', 'MarkerSize', 10)

hold off;