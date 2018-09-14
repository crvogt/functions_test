function LFOut = LFDehex_crv(LF)
    %---Correct for hex grid and resize to square u,v pixels---
    LFSize = size(LF);

    HexAspect =2/sqrt(3); 
    firstPosShiftRow = 1;
    doSquareST = false;

    fprintf('\nResampling (1D approximation) to square u,v pixels');
    NewUVec = 0:1/HexAspect:(size(LF,4)+1);  % overshoot then trim
    NewUVec = NewUVec(1:ceil(LFSize(4)*HexAspect));
    OrigUSize = size(LF,4);
    LFSize(4) = length(NewUVec);
    %---Allocate dest and copy orig LF into it (memory saving vs. keeping both separately)---
    LF2 = zeros(LFSize);
    LF2(:,:,:,1:OrigUSize,:) = LF;
    fprintf('\nLF2 size\n')
    size(LF2)
    LF = LF2;
    clear LF2
    
    ShiftUVec = -0.5+NewUVec;
    fprintf(' and removing hex sampling...');
  
    for ColChan = 1:3
        CurUVec = ShiftUVec;
        for RowIter = 1:2
            RowIdx = mod(firstPosShiftRow + RowIter, 2) + 1;
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
    LFOut = LF;

    %---Resize to square s,t pixels---
    % Assumes only a very slight resampling is required, resulting in an identically-sized output light field
    % if doSquareST
    %     fprintf('\nResizing to square s,t pixels using 1D linear interp...');
    %     % pause(4)
    %     ResizeScale = DecodeOptions.OutputScale(1)/DecodeOptions.OutputScale(2);
    %     ResizeDim1 = 1;
    %     ResizeDim2 = 2;
    %     if( ResizeScale < 1 )
    %         ResizeScale = 1/ResizeScale;
    %         ResizeDim1 = 2;
    %         ResizeDim2 = 1;
    %     end
        
    %     OrigSize = size(LF, ResizeDim1);
    %     OrigVec = floor((-(OrigSize-1)/2):((OrigSize-1)/2));
    %     NewVec = OrigVec ./ ResizeScale;
        
    %     OrigDims = [1:ResizeDim1-1, ResizeDim1+1:5];
        
    %     % fprintf('\nmid pause\n');
    %     % pause(4)

    %     UBlkSize = 32;
    %     USize = size(LF,4);
    %     LF = permute(LF,[ResizeDim1, OrigDims]);
    %     for( UStart = 1:UBlkSize:USize )
    %         UStop = UStart + UBlkSize - 1;
    %         UStop = min(UStop, USize);
    %         LF(:,:,:,UStart:UStop,:) = interp1(OrigVec, LF(:,:,:,UStart:UStop,:), NewVec);
    %         fprintf('.');
    %     end
    %     LF = ipermute(LF,[ResizeDim1, OrigDims]);
    %     LF(isnan(LF)) = 0;
        
    %     DecodeOptions.OutputScale(ResizeDim2) = DecodeOptions.OutputScale(ResizeDim2) * ResizeScale;
    % end

    % fprintf('\nNext Pause...\n');
    % pause(10)
    %---Trim s,t---
    % fprintf('\nPost DoSquareST\n')
    % size(LF)
    % LF = LF(2:end-1,2:end-1, :,:, :);

    %---Slice out LFWeight if it was requested---
    % if( nargout >= 2 )
    %     fprintf('\nSlicing out LFWeight\n');    
    %     LFWeight = LF(:,:,:,:,end);
    %     LFWeight = LFWeight./max(LFWeight(:));
        % LF = LF(:,:,:,:,1:end-1);

    % fprintf('\nNew Pause');
    % pause(4);
    % end

end