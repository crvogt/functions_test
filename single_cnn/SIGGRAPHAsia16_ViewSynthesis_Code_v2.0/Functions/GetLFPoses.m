function lfPoses = GetLFPoses(parmContNames)

lfPoses = zeros(1, 2, length(parmContNames));

fprintf('\nnum of names:%d\n', length(parmContNames));

if length(parmContNames) > 0
	for iter = 1:length(parmContNames)
		[theta, phi] = ParseName(parmContNames{iter});
		lfPoses(1,1,iter) = theta;
		lfPoses(1,2,iter) = phi;
	end
else 
	error('Directory without any contents\n');
end