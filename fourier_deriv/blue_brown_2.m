clc
clear all
close all

a = 1;
f3 = 3.5;
theta = 0:0.01:2*pi;
y = exp(1i*theta);

b = figure(1);

% polarplot(y, '*')
% cla(b)
subplot(1,1,1)
% figure(2)
hold on;
frequency = 1;
% for frequency = 0:0.001:4
%     % for t = 0:0.01:pi
%     t = 0:0.01:pi;
% 
%         y3 = a*cos(2*f3*pi*t) + a;
%         y2 = y3.*exp(-1i * 2*pi*t*frequency);
%     %     hold on
% %         polarplot(y2)
%     %     plot(imag(y2), real(y2), '*k');
%     %     pause(0.1);
%     %     cla(v);
%     % end
%     % hold off;
% 
%     % For cm, 
%     N = length(t);
%     com = sum(y2)/N;
%     plot(frequency, real(com), '*k')
% end

for frequency = 0:0.01:4
    fun = @(t) (a*cos(2*f3*pi.*t) + a).*exp(-1i*2*pi.*t*frequency);
    q = integral(fun, 0, 4);
    plot(frequency, real(q), '*k')
end