indexCreator="../../../RCSO-IndexGenerator/Debug/IndexGenerator"
setOperator="../../../RCSO-RCSetOp/Debug/RelCondSetOps"

printf "\n                  CREATING INDEX FOR T1[0]\n"
printf "==============================================================\n"
./$indexCreator T1.data 0 simple
printf "\n                  CREATING INDEX FOR T1[1]\n"
printf "==============================================================\n"
./$indexCreator T1.data 1 simple

printf "\n               PERFORMING RELATIONAL SET OPERATION\n"
printf "==============================================================\n"
./$setOperator T1.data T2.data query.sql
