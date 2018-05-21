#!/bin/bash
origLoc="$PWD/"
echo $origLoc 
cd ..
cd testDir
copyTo="$PWD"
echo $copyTo
cd $origLoc

for i in $(ls -d $PWD/*/); do
	mypather2="$i"
	echo $mypather2
	cp $mypather2*.txt $copyTo
	echo copy file to
	echo $copyTo
done
