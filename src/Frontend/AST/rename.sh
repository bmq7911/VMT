#!/bin/bash


for file in `ls *.h *.cpp *.hpp *.c` 
do
	if [ -f $file ]
	then
		mv $file "Ast"$file
	fi
done
