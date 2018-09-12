function [lfToShow imgOut] = LFDisp( LF )
fprintf('\nPre squeeze LFDisp\n');
size(LF)
LF = squeeze(LF);
fprintf('\npost squeeze LF\n');
LFSize = size(LF)

GoalDims = 3;

while( ndims(LF) > GoalDims )
	fprintf('\nIn goal dims\n');
	size(LF)
	LF = squeeze(LF(round(end/2),:,:,:,:));
	size(LF)
end

imgOut = uint16(LF);
lfToShow = uint16(LF);

imshow(imgOut)
