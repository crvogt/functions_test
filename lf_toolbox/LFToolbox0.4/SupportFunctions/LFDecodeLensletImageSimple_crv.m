function [LF, DecodeOptions] = ...
    LFDecodeLensletImageSimple(LensletImage)

% %---Defaults---
% DecodeOptions = LFDefaultField( 'DecodeOptions', 'LevelLimits', [min(WhiteImage(:)), max(WhiteImage(:))] );
DecodeOptions = LFDefaultField( 'DecodeOptions', 'ResampMethod', 'triangulation' ); %'fast', 'triangulation'
DecodeOptions = LFDefaultField( 'DecodeOptions', 'Precision', 'single' );
DecodeOptions = LFDefaultField( 'DecodeOptions', 'DoDehex', true );
DecodeOptions = LFDefaultField( 'DecodeOptions', 'DoSquareST', true );

DecodeOptions.NColChans = 3;
DecodeOptions.NWeightChans = 0;

LensletGridModel.HSpacing = 11.585*2;
LensletGridModel.VSpacing = 11.589*2;
LensletGridModel.UMax = 87;
LensletGridModel.VMax = 101;
% LensletGridModel.UMax = 170; %left right
% LensletGridModel.VMax = 170;
% LensletGridModel.HSpacing = 101;
% LensletGridModel.VSpacing = 87;
% LensletGridModel.UMax = 11.585;
% LensletGridModel.VMax = 11.589;
LensletGridModel.HOffset = 0;
LensletGridModel.VOffset = 0;
LensletGridModel.Orientation = 'horz';
LensletGridModel.Rot = 0;
LensletGridModel.FirstPosShiftRow = 1;

%---Tranform to an integer-spaced grid---
fprintf('\nAligning image to lenslet array...');
InputSpacing = [LensletGridModel.HSpacing, LensletGridModel.VSpacing];
NewLensletSpacing = ceil(InputSpacing);
% Force even so hex shift is a whole pixel multiple
NewLensletSpacing = ceil(NewLensletSpacing/2)*2;
XformScale = NewLensletSpacing ./ InputSpacing;  % Notice the resized image will not be square

NewOffset = [LensletGridModel.HOffset, LensletGridModel.VOffset] .* XformScale;
RoundedOffset = round(NewOffset);
XformTrans =  RoundedOffset-NewOffset;

NewLensletGridModel = struct('HSpacing',NewLensletSpacing(1), 'VSpacing',NewLensletSpacing(2), ...
    'HOffset',RoundedOffset(1), 'VOffset',RoundedOffset(2), 'Rot',0, ...
    'UMax', LensletGridModel.UMax, 'VMax', LensletGridModel.VMax, 'Orientation', LensletGridModel.Orientation, ...
    'FirstPosShiftRow', LensletGridModel.FirstPosShiftRow);

%---Fix image rotation and scale---
RRot = LFRotz( LensletGridModel.Rot );

RScale = eye(3);
RScale(1,1) = XformScale(1);
RScale(2,2) = XformScale(2);
DecodeOptions.OutputScale(1:2) = XformScale;
DecodeOptions.OutputScale(3:4) = [1,2/sqrt(3)];  % hex sampling

RTrans = eye(3);
RTrans(end,1:2) = XformTrans;

% The following rotation can rotate parts of the lenslet image out of frame.
% todo[optimization]: attempt to keep these regions, offer greater user-control of what's kept
FixAll = maketform('affine', RRot*RScale*RTrans);
NewSize = size(LensletImage(:,:,1)) .* XformScale(2:-1:1);


LF = SliceXYImage( NewLensletGridModel, LensletImage, DecodeOptions );
% size(LF)
% for iter = 1:size(LF,3)
% for jter = 1:size(LF,4)

%         if jter == 1
%             basicImg = LF(:,:,iter,jter,:);
%             basicImg = squeeze(uint16(basicImg));
%         else 
%             lensImg = LF(:,:,iter,jter,:);
%             lensImg = squeeze(uint16(lensImg));
%             basicImg = cat(2, basicImg, lensImg);
%         end 
%     end
%     if iter == 1
%         fullImg = basicImg;
%     else
%         fullImg = cat(1,fullImg,basicImg);
%     end      
% end 

% imshow(fullImg)
% pause(1000)

fprintf('\nLF size after SliceXYImage\n');
size(LF)
% clear WhiteImage LensletImage
clear LensletImage

%---Correct for hex grid and resize to square u,v pixels---
LFSize = size(LF);
HexAspect =2/sqrt(3);
switch( DecodeOptions.ResampMethod )
    case 'fast'
        fprintf('\nResampling (1D approximation) to square u,v pixels');
        NewUVec = 0:1/HexAspect:(size(LF,4)+1);  % overshoot then trim
        NewUVec = NewUVec(1:ceil(LFSize(4)*HexAspect));
        OrigUSize = size(LF,4);
        LFSize(4) = length(NewUVec);
        %---Allocate dest and copy orig LF into it (memory saving vs. keeping both separately)---
        LF2 = zeros(LFSize, DecodeOptions.Precision);
        LF2(:,:,:,1:OrigUSize,:) = LF;
        fprintf('\nLF2 size\n')
        size(LF2)
        LF = LF2;
        clear LF2
        
        if( DecodeOptions.DoDehex )
            ShiftUVec = -0.5+NewUVec;
            fprintf(' and removing hex sampling...');
        else
            ShiftUVec = NewUVec;
            fprintf('...');
        end
        for( ColChan = 1:size(LF,5) )
            CurUVec = ShiftUVec;
            for( RowIter = 1:2 )
                RowIdx = mod(NewLensletGridModel.FirstPosShiftRow + RowIter, 2) + 1;
                ShiftRows = squeeze(LF(:,:,RowIdx:2:end,1:OrigUSize, ColChan));
                SliceSize = size(ShiftRows);
                SliceSize(4) = length(NewUVec);
                ShiftRows = reshape(ShiftRows, [size(ShiftRows,1)*size(ShiftRows,2)*size(ShiftRows,3), size(ShiftRows,4)]);
                ShiftRows = interp1( (0:size(ShiftRows,2)-1)', ShiftRows', CurUVec' )';
                ShiftRows(isnan(ShiftRows)) = 0;
                LF(:,:,RowIdx:2:end,:,ColChan) = reshape(ShiftRows,SliceSize);
                CurUVec = NewUVec;
            end
        end
        clear ShiftRows
        DecodeOptions.OutputScale(3) = DecodeOptions.OutputScale(3) * HexAspect;
        fprintf('\nPaused...\n');
        % pause(10)
    case 'triangulation'
        fprintf('\nResampling (triangulation) to square u,v pixels');
        OldVVec = (0:size(LF,3)-1);
        OldUVec = (0:size(LF,4)-1) * HexAspect;
        
        NewUVec = (0:ceil(LFSize(4)*HexAspect)-1);
        NewVVec = (0:LFSize(3)-1);
        LFSize(4) = length(NewUVec);
        LF2 = zeros(LFSize, DecodeOptions.Precision);
        
        [Oldvv,Olduu] = ndgrid(OldVVec,OldUVec);
        [Newvv,Newuu] = ndgrid(NewVVec,NewUVec);
        if( DecodeOptions.DoDehex )
            fprintf(' and removing hex sampling...');
            % pause(10);
            FirstShiftRow = NewLensletGridModel.FirstPosShiftRow;
            Olduu(FirstShiftRow:2:end,:) = Olduu(FirstShiftRow:2:end,:) + HexAspect/2;
        else
            fprintf('...');
        end
        
        DT = delaunayTriangulation( Olduu(:), Oldvv(:) );  % use DelaunayTri in older Matlab versions
        [ti,bc] = pointLocation(DT, Newuu(:), Newvv(:));
        ti(isnan(ti)) = 1;
        
        for( ColChan = 1:size(LF,5) )
            fprintf('.');
            for( tidx= 1:LFSize(1) )
                for( sidx= 1:LFSize(2) )
                    CurUVSlice = squeeze(LF(tidx,sidx,:,:,ColChan));
                    triVals = CurUVSlice(DT(ti,:));
                    CurUVSlice = dot(bc',triVals')';
                    CurUVSlice = reshape(CurUVSlice, [length(NewVVec),length(NewUVec)]);
                    
                    CurUVSlice(isnan(CurUVSlice)) = 0;
                    LF2(tidx,sidx, :,:, ColChan) = CurUVSlice;
                end
            end
        end
        LF = LF2;
        clear LF2
        DecodeOptions.OutputScale(3) = DecodeOptions.OutputScale(3) * HexAspect;
        
    otherwise
        fprintf('\nNo valid dehex / resampling selected\n');
end

fprintf('End of switch case LF size\n')
size(LF)

%---Resize to square s,t pixels---
% Assumes only a very slight resampling is required, resulting in an identically-sized output light field
if( DecodeOptions.DoSquareST )
    fprintf('\nResizing to square s,t pixels using 1D linear interp...');
    % pause(4)
    ResizeScale = DecodeOptions.OutputScale(1)/DecodeOptions.OutputScale(2);
    ResizeDim1 = 1;
    ResizeDim2 = 2;
    if( ResizeScale < 1 )
        ResizeScale = 1/ResizeScale;
        ResizeDim1 = 2;
        ResizeDim2 = 1;
    end
    
    OrigSize = size(LF, ResizeDim1);
    OrigVec = floor((-(OrigSize-1)/2):((OrigSize-1)/2));
    NewVec = OrigVec ./ ResizeScale;
    
    OrigDims = [1:ResizeDim1-1, ResizeDim1+1:5];
    
    % fprintf('\nmid pause\n');
    % pause(4)

    UBlkSize = 32;
    USize = size(LF,4);
    LF = permute(LF,[ResizeDim1, OrigDims]);
    for( UStart = 1:UBlkSize:USize )
        UStop = UStart + UBlkSize - 1;
        UStop = min(UStop, USize);
        LF(:,:,:,UStart:UStop,:) = interp1(OrigVec, LF(:,:,:,UStart:UStop,:), NewVec);
        fprintf('.');
    end
    LF = ipermute(LF,[ResizeDim1, OrigDims]);
    LF(isnan(LF)) = 0;
    
    DecodeOptions.OutputScale(ResizeDim2) = DecodeOptions.OutputScale(ResizeDim2) * ResizeScale;
end

% fprintf('\nNext Pause...\n');
% pause(10)
%---Trim s,t---
fprintf('\nPost DoSquareST\n')
size(LF)
LF = LF(2:end-1,2:end-1, :,:, :);

%---Slice out LFWeight if it was requested---
if( nargout >= 2 )
    fprintf('\nSlicing out LFWeight\n');    
    LFWeight = LF(:,:,:,:,end);
    LFWeight = LFWeight./max(LFWeight(:));
    % LF = LF(:,:,:,:,1:end-1);

% fprintf('\nNew Pause');
% pause(4);
end

end

%------------------------------------------------------------------------------------------------------
function LF = SliceXYImage( LensletGridModel, LensletImage, DecodeOptions )
% todo[optimization]: The SliceIdx and ValidIdx variables could be precomputed

fprintf('\nSlicing lenslets into LF...');

% pause(10)

USize = LensletGridModel.UMax;
VSize = LensletGridModel.VMax;
MaxSpacing = max(LensletGridModel.HSpacing, LensletGridModel.VSpacing);  % Enforce square output in s,t
SSize = MaxSpacing + 1; % force odd for centered middle pixel -- H,VSpacing are even, so +1 is odd
TSize = MaxSpacing + 1;

LF = zeros(TSize, SSize, VSize, USize, DecodeOptions.NColChans + DecodeOptions.NWeightChans, DecodeOptions.Precision);

fprintf('\nLF size\n')
size(LF)
% pause(3)

TVec = cast(floor((-(TSize-1)/2):((TSize-1)/2)), 'int16');
SVec = cast(floor((-(SSize-1)/2):((SSize-1)/2)), 'int16');
% fprintf('\nsvec size\n')
% size(SVec)
VVec = cast(0:VSize-1, 'int16');
% fprintf('\nvvec size\n')
% size(VVec)
% pause(2)
UBlkSize = 32

    for( UStart = 0:UBlkSize:USize-1 )  % note zero-based indexing
        UStop = UStart + UBlkSize - 1;
        UStop = min(UStop, USize-1);  
        UVec = cast(UStart:UStop, 'int16');
        
        [tt,ss,vv,uu] = ndgrid( TVec, SVec, VVec, UVec );
        
        %---Build indices into 2D image---
        LFSliceIdxX = LensletGridModel.HOffset + uu.*LensletGridModel.HSpacing + ss;
        LensletGridModel.HOffset
        size(uu)
        size(vv)
        size(ss)
        size(tt)
        LFSliceIdxY = LensletGridModel.VOffset + vv.*LensletGridModel.VSpacing + tt;
        
        fprintf('\nFirst of Slice:\n')
        size(LFSliceIdxX)
        % pause(2)

        HexShiftStart = LensletGridModel.FirstPosShiftRow;
        LFSliceIdxX(:,:,HexShiftStart:2:end,:) = LFSliceIdxX(:,:,HexShiftStart:2:end,:) + LensletGridModel.HSpacing/2;
        


        %---Lenslet mask in s,t and clip at image edges---
        CurSTAspect = DecodeOptions.OutputScale(1)/DecodeOptions.OutputScale(2);
        % fprintf('\nCurSTAspect:\n')
        % CurSTAspect
        % fprintf('\nDecodeOptions.OutputScale(1) and (2)\n')
        % DecodeOptions.OutputScale(1)
        % DecodeOptions.OutputScale(2)
        % pause(10)

        R = sqrt((cast(tt,DecodeOptions.Precision)*CurSTAspect).^2 + cast(ss,DecodeOptions.Precision).^2);
    
        % LFSliceIdxX(6,6,87,32) = 0;
        ValidIdx = find(R < LensletGridModel.HSpacing/2 & ...
            LFSliceIdxX >= 1 & LFSliceIdxY >= 1 & LFSliceIdxX <= size(LensletImage,2) & LFSliceIdxY <= size(LensletImage,1) );
        % fprintf('LensletImage size\n')
        % R(:,:,87,32)
        % length(ValidIdx)
        % size(LensletImage)
        % size(R)
        % size(LFSliceIdxX)
        % LFSliceIdxX <= 1
        % pause(10)
        
        %--clip -- the interp'd values get ignored via ValidIdx--
        fprintf('\nLensletImage,2\n')
        size(LensletImage,2);
        min(size(LensletImage,2), LFSliceIdxX);
        LFSliceIdxX(:,:,1,1);
        % pause(10)

        LFSliceIdxX = max(1, min(size(LensletImage,2), LFSliceIdxX ));
        LFSliceIdxY = max(1, min(size(LensletImage,1), LFSliceIdxY ));
        fprintf('\nPost max operation\n')
        % LFSliceIdxX(:,:,1,1)
        % LFSliceIdxY(:,:,1,1)
        size(LFSliceIdxY)
        size(LFSliceIdxX)
        size(LensletImage)

        LFSliceIdx = sub2ind(size(LensletImage), cast(LFSliceIdxY,'int32'), ...
            cast(LFSliceIdxX,'int32'), ones(size(LFSliceIdxX),'int32'));
        % size(LFSliceIdx)
        % LFSliceIdx;
        % pause(10)
        % tt(:,:,87,32)
        % min(tt(:))
        % pause(2)
        tt = tt - min(tt(:)) + 1;
        % pause(2)
        % tt(:,:,87,32)
        % pause(10)
        ss = ss - min(ss(:)) + 1;
        % ss(:,:,87,32)
        % pause(10)
        vv = vv - min(vv(:)) + 1;
        % vv(:,:,86,32)
        % pause(10)
        uu = uu - min(uu(:)) + 1 + UStart;
        LFOutSliceIdx = sub2ind(size(LF), cast(tt,'int32'), cast(ss,'int32'), ...
            cast(vv,'int32'),cast(uu,'int32'), ones(size(ss),'int32'));
        
        %---
        for( ColChan = 1:DecodeOptions.NColChans )
            LF(LFOutSliceIdx(ValidIdx) + numel(LF(:,:,:,:,1)).*(ColChan-1)) = ...
                LensletImage( LFSliceIdx(ValidIdx) + numel(LensletImage(:,:,1)).*(ColChan-1) );
        end
        % if( DecodeOptions.NWeightChans ~= 0 )
        %     LF(LFOutSliceIdx(ValidIdx) + numel(LF(:,:,:,:,1)).*(DecodeOptions.NColChans)) = ...
        %         WhiteImage( LFSliceIdx(ValidIdx) );
        % end
        fprintf('.');
    end
    vv.*LensletGridModel.VSpacing
    max(max(max(max(LFSliceIdxX(:,:,:,:)))))
    max(max(max(max(LFSliceIdxY(:,:,:,:)))))
    % pause(20);
end