clc
clear all
close all

listOfFiles = dir('/media/carson/WDPassport/deep_learn/pr2_dataset/set_1/sphere_param/');

% dataCell = cell(length(listOfFiles), 5);
thetaArr = zeros(length(listOfFiles)-2,1);
phiArr = zeros(length(listOfFiles)-2,1);
numArr = zeros(length(listOfFiles)-2,1);
% nameArr = zeros(length(listOfFiles)-2,1);
iterArr = zeros(length(listOfFiles)-2,1);

negVal = false;

for jt = 3:length(listOfFiles)
	from = 1;
	parts = 1;
	firstName = listOfFiles(jt).name;
	for it = 1:length(firstName)
		if(firstName(it) == '_')
			if(parts == 1)
				number = str2num(firstName(from:(it-1)));
				from = it + 1;
				parts = parts + 1;
			elseif(parts == 2)
				negCheck = firstName(from:(it-1));
				if negCheck(1) == '-'
					negVal = true;
				else 
					negVal = false;
				end
				theta = str2num(firstName(from:(it-1)));
				from = it + 1;
				parts = parts + 1;
			elseif(parts == 3)
				temp = str2num(firstName(from:(it-1)));
				temp = temp /(10^(length(firstName(from:(it-1)))));
				if negVal
					theta = theta - temp;
				else 
					theta = theta + temp;
				end
				from = it + 1;
				parts = parts + 1;
			elseif parts == 4
				negCheck = firstName(from:(it-1));
				if negCheck(1) == '-'
					negVal = true;
					error('negative phi val');
					while true
					end
				else 
					negVal = false;
				end
				phi = str2num(firstName(from:(it-1)));
				from = it + 1;
				parts = parts + 1;
			end
		elseif(firstName(it) == '.')
			temp = str2num(firstName(from:(it-1)));
			temp = temp /(10^(length(firstName(from:(it-1)))));
			phi = phi + temp;
		end
	end
	% fprintf('Num: %d, theta: %f, phi: %f, iter: %d\n', number, theta, phi, (jt-2));
	thetaArr(jt-2) = theta;
	phiArr(jt-2) = phi;
	numArr(jt-2) = number;
	iterArr(jt-2) = jt-2;
	firstName = string(firstName);
	if (jt-2) == 1
		nameArr = firstName;
	else 
		nameArr = [nameArr; firstName];
	end
end

data.thetaArr = thetaArr;
data.phiArr = phiArr;
data.numArr = numArr;
data.iterArr = iterArr;
data.nameArr = nameArr;
