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
    % fprintf('\nLF2 size\n')
    % size(LF2)
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
end