clc
clear all 
close all
% % 
% % counter = 0;
% % 
% % xC = 0.1;
% % yC = 0.1;
% % 
% % zMax = 0.10;
% % 
% % al = 0.01;
% % 
% % R = zMax;
% % r = 0;
% % 
% % C = 0;
% % z = zMax - 0.00001;
% % 
% % figure(1)
% % hold on;
% % 
% % while(z >= 0)
% %     r = sqrt(R^2 - z^2)
% %     CI = (2 * pi * al) / (2*pi*R);
% %     
% %     while(C < 2*pi)
% % 
% %         C = C + CI;
% % 
% %         x = R * cos(C);
% %         y = R * sin(C);
% % 
% %         %x = x + xC;
% %         %y = y + yC;
% % 
% %         plot3(x, y, z, '*', 'MarkerSize', 10)
% %         axis([-0.5 0.5 -0.5 0.5, -0.5, 0.5])
% %         grid on;
% % 
% %         counter = counter + 1;
% % 
% % 
% %     end
% %     C = 0;
% %     z = z - 0.01
% % end
% % 
% % counter
% % 
% % hold off;
% % 
% % density = counter;
% % 
% % %Now for a planar surface
% % depth = 0;
% % 
% % lengthMin = 0;
% % lengthMax = 2 * pi * R;
% % heightMin = 0;
% % heightMax = zMax;
% % 
% % intervalArea = 0;
% % 
% % figure(2)
% % hold on;
% % 
% % 
% % 
% % hold off;

% areaTarget = 75 * .3275*0.4;
% area = 0;
% hp = 0.3275/0.4;
% wp = 1;
% while(area < areaTarget)
%    temp = area;
%    area = hp * wp;
%    hp = hp * 1.001;
%    wp = wp * 1.001;
% end
% 
% temp
% area
% hp
% wp




%%%%%%%%%%%%%%%%fibonacci%%%%%%%%%%%%%%%%%%%%%%%%%%%%
ng = 1200 * 2;
maxR = 2

phi = ( 1.0 + sqrt ( 5.0 ) ) / 2.0

i = ( - ( ng - 1 ) : 2 : ( ng - 1 ) )';
theta = 2 * pi * i / phi;
sphi = i / (ng/maxR)
cphi = sqrt ( ( ng + i ) .* ( ng - i ) ) / (ng/maxR)

xg = zeros ( ng/2, 3 );

xg(1:ng,1) = cphi .* sin ( theta );
xg(1:ng,2) = cphi .* cos ( theta );
xg(1:ng,3) = sphi;

figure ( )
clf
hold on
[ x, y, z ] = sphere ( 20 );
x = (maxR - 0.05) * x;
y = (maxR - 0.05) * y;
z = (maxR - 0.05) * z;
c = ones ( size ( z ) );
% surf ( x, y, z, c );
plot3 ( xg(:,1), xg(:,2), xg(:,3), 'b.', 'Markersize', 20 );
axis equal
grid on
view ( 3 )
xlabel ( '<--X-->' )
ylabel ( '<--Y-->' )
zlabel ( '<--Z-->' )
title ( sprintf ( '%d point Fibonacci Grid on Sphere', ng ), 'FontSize', 24 );
hold off

print ( '-dpng', filename );
fprintf ( 1, '\n' );
fprintf ( 1, '  Plot file saved to "%s".\n', filename );







