#!/bin/bash

# All paths are from the point of view of the inside directory (TEST x/y)
indexCreator="../../../../../RCSO-IndexGenerator/Debug/IndexGenerator"
setOperator="../../../../../RCSO-RCSetOp/Debug/RelCondSetOps"
queryIntersect="../../queryIntersect.sql"
queryMinus="../../queryMinus.sql"
queryMemberEach="../../queryMemberEach.sql"
querySubset="../../querySubset.sql"

for n in {5..5}
do 
	cd "TEST "$n
	for m in {0..0}
	do
		cd $m
		printf "\n********************** TEST "$n"/"$m"***********************\n"
		printf "\n                  CREATING INDEX FOR T1[0]\n"
		printf "==============================================================\n"
		./$indexCreator T1.data 0 simple
		printf "\n                  CREATING INDEX FOR T1[1]\n"
		printf "==============================================================\n"
		./$indexCreator T1.data 1 simple
		printf "\n                  CREATING INDEX FOR T1[2]\n"
		printf "==============================================================\n"
		./$indexCreator T1.data 2 simple
		printf "\n                  CREATING INDEX FOR T1[3]\n"
		printf "==============================================================\n"
		./$indexCreator T1.data 3 simple
		printf "\n                  CREATING INDEX FOR T2[0]\n"
		printf "==============================================================\n"
		./$indexCreator T2.data 0 simple
		printf "\n                  CREATING INDEX FOR T2[1]\n"
		printf "==============================================================\n"
		./$indexCreator T2.data 1 simple
		printf "\n                  CREATING INDEX FOR T2[2]\n"
		printf "==============================================================\n"
		./$indexCreator T2.data 2 simple
		printf "\n                  CREATING INDEX FOR T2[3]\n"
		printf "==============================================================\n"
		./$indexCreator T2.data 3 simple
		
		for time in {1..1}
		do
			printf "\n********************** TEST "$n"/"$m"/ time: "$time"***********************\n"
			printf "\n               PERFORMING REL COND INTERSECTION \n"
			printf "==============================================================\n"
			./$setOperator T1.data T2.data $queryIntersect -index T1
			printf "\n               PERFORMING REL COND DIFFERENCE \n"
			printf "==============================================================\n"
			./$setOperator T1.data T2.data $queryMinus -index T1
			printf "\n               PERFORMING REL COND SUBSET \n"
			printf "==============================================================\n"
			./$setOperator T1.data T2.data $querySubset -index T1
			printf "\n               PERFORMING REL COND MEMBERSHIP \n"
			printf "==============================================================\n"
			./$setOperator T2.data T1.data $queryMemberEach -index T1
				
		done
		cd .. # TEST n
	done
	cd .. # TESTS
done
