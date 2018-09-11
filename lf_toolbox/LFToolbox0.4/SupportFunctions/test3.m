clear all 
close all
clc

svec = -6:6;
tvec = -6:6;
uvec = 96:100;
vvec = 0:86;

[tt, ss, vv, uu] = ndgrid(tvec, svec, vvec, uvec);

LFSliceIdxX = uu.*11.58 + ss;
LFSliceIdxY = vv.*11.58 + tt;
