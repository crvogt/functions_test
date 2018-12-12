% Pull from dark images
% Compare with enhanced and ref


	LF = get_sub_ap(imgPath);

	delete(strcat(writeDir, '/*.png'));

	pxStart = 6;
	pxEnd = 20;
	pxDist = 1;
	nCols = pxEnd - pxStart;
	nRows = nCols;

	icounter = 1;
	jcounter = 1;

	iter 13;
	jter 13;
	% img = uint16(squeeze(LF(iter,jter,:,:,:)));
	img = uint8(squeeze(LF(iter, jter, :, :, :)));
	filename = '';

	imwrite(img, filename)

