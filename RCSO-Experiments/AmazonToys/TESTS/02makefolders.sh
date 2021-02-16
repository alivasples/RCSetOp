#!/bin/bash
for n in {5..5}
do 
	mkdir "TEST "$n
	cd "TEST "$n
	for m in {1..100}
	do
		mkdir $m
	done
	cd ..
done
