function get_sais(imgPath, folderName)
    
    writeDir = folderName
	LF = get_sub_ap(imgPath);
	LFWriteOutDepthSAI_crv(LF, folderName);
end