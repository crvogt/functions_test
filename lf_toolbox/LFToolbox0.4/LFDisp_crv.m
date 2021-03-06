function [lfToShow, imgOut] = LFDisp_crv( LF )
fprintf('\nPre squeeze LFDisp\n');
size(LF);
LF = squeeze(LF);
fprintf('\npost squeeze LF\n');
LFSize = size(LF);

GoalDims = 3;

while( ndims(LF) > GoalDims )	
	LF = squeeze(LF(round(end/2),:,:,:,:));
end

imgOut = uint16(LF);
lfToShow = uint16(LF);

% size(imgOut)

% imshow(uint8(imgOut));
