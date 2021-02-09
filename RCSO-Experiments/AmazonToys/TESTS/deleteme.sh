#!/bin/bash

# All paths are from the point of view of the inside directory (TEST x/y)
indexCreator="../../../../../RCSO-IndexGenerator/Debug/IndexGenerator"
setOperator="../../../../../RCSO-RCSetOp/Debug/RelCondSetOps"
queryIntersect="../../queryIntersect.sql"
queryMinus="../../queryMinus.sql"
queryMember="../../queryMembership.sql"
queryMemberEach="../../queryMemberEach.sql"
querySubset="../../querySubset.sql"

for n in {1..5}
do 
	cd "TEST "$n
	for m in {1..100}
	do
		cd $m
		for time in {1..10}
		do
			printf "\n********************** TEST "$n"/"$m"/ time: "$time"***********************\n"
			printf "\n               PERFORMING REL COND MEMBERSHIP \n"
			printf "==============================================================\n"
			./$setOperator T1.data T2.data $queryMemberEach -index T1
				
		done
		cd .. # TEST n
	done
	cd .. # TESTS
done
