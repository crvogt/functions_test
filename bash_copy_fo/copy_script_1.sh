#!/bin/bash

for i in $(ls); do 
	echo item: $i
	mypather='mypath'
	mypather2="$mypather$i"
	echo $mypather2
done
