clc
%%%%%%%%%%%%%%%%%%%%%%%Mathematical Monk%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% kernel = 3
% switch kernel
%     case 1; k = @(x,y) 1*x'*y; %linear
%     case 2; k = @(x,y) 1*min(x,y); %brownian
%     case 3; k = @(x,y) exp(-100*(x-y)'*(x-y));
% end
% 
% %Choose points at which to sample
% x = (0:0.1:1);
% n = length(x);
% 
% %Construct the covariance matrix
% C = zeros(n,n);
% for i = 1:n
%     for j = 1:n
%         C(i,j) = k(x(i),x(j));
%     end
% end
% C;
% %Sample from the Gaussian process
% u = randn(n,1)     %sample u ~ N(0,I)
% [A,S,B] = svd(C);   %factor C = ASB'
% z = A*sqrt(S)*u    %z = A S^.5 u ~
% 
% %plot
% figure(1); hold on; clf
% plot(x,z,'.-')
% axis([0,1,-2,2])
% figure(4); hold on; clf
% plot(x, z, '*k')


%%%%%%%%%%%The Normal Distribution from CM Lecture%%%%%%%%%%%%%%%%%%%%%%%%
% x = (-1:0.005:1);
% sigma = .5; %Variance, but will leave as const for now
% mew = 0;
% p = (1 / sqrt(2 * pi * sigma^2)) * exp((-1 / (2 * sigma^2)) * ((x - mew).^2));
% 
% figure(2); hold on; clf
% plot(x, p, '.-') 
% %axis([0, 1, -2, 2])

%%%%%%%%%%%%%%%%%%Computing mu and sigma%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%if sigma is our covariance matrix, what do we get here...
% x = [19 18 19.7 21 24.1 25.7 23.3 18 17 20 21 20.8 20.99 19 20 20 21.122 22 20 22]; % 20 values for x...
% m = length(x); %This is the sample size
% sumVal = 0;
% 
% for i = 1:m
%     sumVal = sumVal + x(i);
% end
% 
% mu = sumVal / m;
% 
% sumVal = 0;
% 
% for i = 1:m    
%     sumVal = sumVal + x(i)*x(i)' - mu*mu';
% end
% 
% sigma = sumVal / m;
% 
% p = (1 / sqrt(2 * pi * sigma^2)) * exp((-1 / (2 * sigma^2)) * ((x - mu).^2));
% 
% figure(3); hold on; clf
% plot(x, p, '*')
% axis([16, 26, 0.04, 0.1])

%%%%%%%%%%%%%%%%%%%Sampling from a Gaussian%%%%%%%%%%%%%%%%%%%
%Still not sure what this one was about...
scale = 0.00015;

quiver3(x,y,z,u,v,w, scale)
hold on
axis([-3.15349 -3.15153 55.8615 55.8623 0 50])
hold off