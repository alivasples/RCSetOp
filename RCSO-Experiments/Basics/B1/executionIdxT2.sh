indexCreator="../../../RCSO-IndexGenerator/Debug/IndexGenerator"
setOperator="../../../RCSO-RCSetOp/Debug/RelCondSetOps"

printf "\n                  CREATING INDEX FOR T1[0]\n"
printf "==============================================================\n"
./$indexCreator T2.data 0 simple
printf "\n                  CREATING INDEX FOR T1[1]\n"
printf "==============================================================\n"
./$indexCreator T2.data 1 simple
printf "\n                  CREATING INDEX FOR T1[2]\n"
printf "==============================================================\n"
./$indexCreator T2.data 2 simple
printf "\n                  CREATING INDEX FOR T1[3]\n"
printf "==============================================================\n"
./$indexCreator T2.data 3 simple

printf "\n               PERFORMING RELATIONAL SET OPERATION\n"
printf "==============================================================\n"
./$setOperator T1.data T2.data queryIdxT2.sql -index T2
