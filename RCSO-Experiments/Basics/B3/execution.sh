indexCreator="../../../RCSO-IndexGenerator/Debug/IndexGenerator"
setOperator="../../../RCSO-RCSetOp/Debug/RelCondSetOps"

printf "\n                  CREATING INDEX FOR T1[0]\n"
printf "==============================================================\n"
./$indexCreator DESIRED.data 0 simple
printf "\n                  CREATING INDEX FOR T1[1]\n"
printf "==============================================================\n"
./$indexCreator DESIRED.data 1 simple
printf "\n                  CREATING INDEX FOR T1[2]\n"
printf "==============================================================\n"
./$indexCreator DESIRED.data 2 simple
printf "\n                  CREATING INDEX FOR T1[3]\n"
printf "==============================================================\n"
./$indexCreator DESIRED.data 3 simple

printf "\n               PERFORMING RELATIONAL SET OPERATION\n"
printf "==============================================================\n"
./$setOperator DESIRED.data STORE.data query.sql
