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

























