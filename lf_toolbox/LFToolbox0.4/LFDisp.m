% LFDisp - Convenience function to display a 2D slice of a light field
% 
% Usage: 
%     LFSlice = LFDispMousePan( LF )
%               LFDispMousePan( LF )
%     
% 
% The centermost image is taken in s and t. Also works with 3D arrays of images. If an output argument is included, no
% display is generated, but the extracted slice is returned instead.
% 
% Inputs:
% 
%     LF : a colour or single-channel light field, and can a floating point or integer format. For
%          display, it is scaled as in imagesc.  If LF contains more than three colour
%          channels, as is the case when a weight channel is present, only the first three are used.
% 
% 
% Outputs:
% 
%     LFSlice : if an output argument is used, no display is generated, but the extracted slice is returned.
%
%
% See also:  LFDispVidCirc, LFDispMousePan

% Part of LF Toolbox v0.4 released 12-Feb-2015
% Copyright (c) 2013-2015 Donald G. Dansereau


function [lfToShow ImgOut] = LFDisp( LF )
fprintf('\nPre squeeze LFDisp\n');
size(LF)
LF = squeeze(LF);
fprintf('\npost squeeze LF\n');
LFSize = size(LF)

HasWeight = (ndims(LF)>2 && LFSize(end)==2 || LFSize(end)==4);
HasColor = (ndims(LF)>2 && (LFSize(end)==3 || LFSize(end)==4) );
HasMonoAndWeight = (ndims(LF)>2 && LFSize(end)==2);

if( HasColor || HasMonoAndWeight )
	GoalDims = 3;
else
	fprintf('\nThem dims\n');
	GoalDims = 2;
end
while( ndims(LF) > GoalDims )
	fprintf('\nIn goal dims\n');
	size(LF)
	LF = squeeze(LF(round(end/2),:,:,:,:));
	size(LF)
end
if( HasWeight )
	fprintf('\nHas weight:\n');
    LF = squeeze(LF(:,:,1:end-1));
    % LF = squeeze(LF(:,:,:));
    size(LF)
end

if( nargout > 0 )
	fprintf('\nnargout greater than 0\n');
	% ImgOut = zeros(87,117,3,'uint16');
	ImgOut = uint16(LF);
	% lfToShow = zeros(87,117,3,'uint16');
	lfToShow = uint16(LF);
else
	fprintf('\nBefore Showing\n');
	size(LF)
	lfToShow = LF;
	% lfToShow
	% imagesc(LF);
	imshow(LF);
end


