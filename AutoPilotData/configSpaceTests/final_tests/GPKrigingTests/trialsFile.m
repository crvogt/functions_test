 clc 
 clear all 
% 
% kernel = 3
%  switch kernel
%      case 1; k = @(x,y) 1*x'*y; %linear
%      case 2; k = @(x,y) 1*min(x,y); %brownian
%      case 3; k = @(x,y) exp(-100*(x-y)'*(x-y));
%  end
%  
%  %Choose points at which to sample
%  x = (0:0.1:1);
%  n = length(x);
%  
%  %Construct the covariance matrix
%  C = zeros(n,n);
%  for i = 1:n
%      for j = 1:n
%          C(i,j) = k(x(i),x(j));
%      end
%  end
%  C;
%  %Sample from the Gaussian process
%  u = randn(n,1)     %sample u ~ N(0,I)
%  [A,S,B] = svd(C);   %factor C = ASB'
%  z = A*sqrt(S)*u;    %z = A S^.5 u ~
%  
%  S
%  
%  sqrt(S)
%  %plot
%  figure(1); hold on; clf
%  plot(x,z,'.-')
%  xlabel('x')
%  ylabel('z')
%  axis([0,1,-2,2])
%  figure(4); hold on; clf
%  plot(x, z, '*k')
%  xlabel('x')
%  ylabel('z')

% %% Initialize variables.
% filename = '/home/carson/ProgrammingFun/AutoPilotData/configSpaceTests/interpolationRun.csv';
% delimiter = ',';
% 
% %% Format string for each line of text:
% %   column1: double (%f)
% %	column2: double (%f)
% %   column3: double (%f)
% %	column4: double (%f)
% %   column5: double (%f)
% %	column6: double (%f)
% % For more information, see the TEXTSCAN documentation.
% formatSpec = '%f%f%f%f%f%f%[^\n\r]';
% 
% %% Open the text file.
% fileID = fopen(filename,'r');
% 
% %% Read columns of data according to format string.
% % This call is based on the structure of the file used to generate this
% % code. If an error occurs for a different file, try regenerating the code
% % from the Import Tool.
% dataArray = textscan(fileID, formatSpec, 'Delimiter', delimiter, 'EmptyValue' ,NaN, 'ReturnOnError', false);
% 
% %% Close the text file.
% fclose(fileID);
% 
% %% Post processing for unimportable data.
% % No unimportable data rules were applied during the import, so no post
% % processing code is included. To generate code which works for
% % unimportable data, select unimportable cells in a file and regenerate the
% % script.
% 
% %% Allocate imported array to column variable names
% x = dataArray{:, 1};
% y = dataArray{:, 2};
% z = dataArray{:, 3};
% u = dataArray{:, 4};
% v = dataArray{:, 5};
% w = dataArray{:, 6};
% 
% 
% %% Clear temporary variables
% clearvars filename delimiter formatSpec fileID dataArray ans;
% 
% %Now to write covariance function
% %number of input dimensions is 3
% 
% %Hyperparameters
% sigma_f = 1;
% lengthParm = [1 1 1];
% sum = 0;
% 
% sigma_f = sigma_f^2;
% for i = 1:length(x)
%     for j = 1:length(x)
%         for d = 1:3
%             if(d == 1)
%                 sum = sum + -1/(2*(lengthParm(d)^2))*(x(i) - x(j))^2;
%             elseif(d == 2)
%                 sum = sum + -1/(2*(lengthParm(d)^2))*(y(i) - y(j))^2;
%             elseif(d == 3)
%                 sum = sum + -1/(2*(lengthParm(d)^2))*(z(i) - z(j))^2;
%             end
%         end
%         
%         k_ff(i,j) = sigma_f * exp(sum);
%         
%         %reset sum
%         sum = 0; 
%         i
%         j
%     end      
% end
% 
% k_ff
  

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
 
       
x = -5:0.1:5;

%prior
sigma_noise = 2;

epsi = sigma_noise*eye(length(x));
for i = 1:length(x)
    plotValsTop(i) = epsi(i, i);
end

u = randn(length(x),1);
L = chol(epsi);
f = L*u; 

plotValsBot = -plotValsTop;
mean = 0;

figure(1);
hold on;
plot(x, mean,'*k')
plot(x, f)
plot(x, plotValsTop, 'k')
plot(x, plotValsBot, 'k')
hold off;

























