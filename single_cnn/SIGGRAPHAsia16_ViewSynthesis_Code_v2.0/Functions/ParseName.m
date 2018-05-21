function [theta, phi] = ParseName(parmName)

negVal = false;
parts = 1;

for it = 1:length(parmName)
	if(parmName(it) == '_')
		if(parts == 1)
			from = it + 1;
			parts = parts + 1;
		elseif(parts == 2)
			negCheck = parmName(from:(it-1));
			if negCheck(1) == '-'
				negVal = true;
			else 
				negVal = false;
			end
			theta = str2num(parmName(from:(it-1)));
			from = it + 1;
			parts = parts + 1;
		elseif(parts == 3)
			temp = str2num(parmName(from:(it-1)));
			temp = temp /(10^(length(parmName(from:(it-1)))));
			if negVal
				theta = theta - temp;
			else 
				theta = theta + temp;
			end
			from = it + 1;
			parts = parts + 1;
		elseif parts == 4
			negCheck = parmName(from:(it-1));
			if negCheck(1) == '-'
				negVal = true;
				error('negative phi val');
				while true
				end
			else 
				negVal = false;
			end
			phi = str2num(parmName(from:(it-1)));
			from = it + 1;
			parts = parts + 1;
		end
	elseif(parmName(it) == '.')
		temp = str2num(parmName(from:(it-1)));
		temp = temp /(10^(length(parmName(from:(it-1)))));
		phi = phi + temp;
	end
end

% theta
% phi