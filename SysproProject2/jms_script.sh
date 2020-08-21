#!/bin/bash
# store arguments in a special array 
args=("$@") 
ELEMENTS=${#args[@]} 
for (( i=0;i<$ELEMENTS;i++)); do 

	if [ ${args[${i}]} == "-c" ];then
		command="${args[$(($i+1))]}"
	fi 
	if [ ${args[${i}]} == "-l" ];then
		path="${args[$(($i+1))]}"
	fi 

done	
if [ $command == "list" ];then
	ls -l $path
fi
if [ $command == "purge" ];then
	rm -rf $path/*sdi1400266*
	rm -rf $path/*pool*
fi
if [[ $command == "size" && $ELEMENTS -eq 4 ]];then
	 ls $path -tr -l -S
fi

if [[ $command == "size" && $ELEMENTS -eq 5 ]];then
	ls $path -tr -l -S | tail -${args[$(($ELEMENTS-1))]}
fi
