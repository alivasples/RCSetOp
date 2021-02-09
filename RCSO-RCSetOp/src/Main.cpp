//============================================================================
// Name        : RelCondSetOps.cpp
// Author      : alivasples
// Version     : 1.0
// Description : Program to perform the Relational Conditional Set Operations
//============================================================================

#include <iostream>
#include <fstream>
#include <algorithm>

#include <Generics.h>
#include <Expression.h>
#include <RCSetOperator.h>

using namespace std;

Expression readQuery(const string &path, string &T1, string &T2, string &setOp){
	// Variables definition
	string condition, tmp;

	// Open query file
	ifstream input(path);
	// Validating that file could be opened
	if(!input.is_open()){
		cout << "File " << path << " could not be opened!" << endl;
		exit(0);
	}

	// Reading the operation
	input >> T1 >> setOp >> T2 >> tmp;
	transform(setOp.begin(), setOp.end(), setOp.begin(), ::toupper);
	// Reading the condition
	condition = "";
	while(input >> tmp){
		condition += tmp + " ";
	}

	// Closing query file
	input.close();
	return Expression(condition);
}

/** Just the main function */
int main(int argc, char* argv[]) {
	// Validating execution
	if(argc < 4){
		cout << "Please execute this file with the next format:\n   ./RelCondSetOps T1.data T2.data query.sql\n\n";
		exit(0);
	}

	// Setting general flags
	string index = "";
	for(int i = 4; i < argc; i++){
		if(strcmp(argv[i], "-debug") == 0) Generics::isDebugMode = true;
		if(strcmp(argv[i], "-index") == 0) index = string(argv[++i]);
	}


	// Variables definition
	string pathT1 = argv[1], pathT2 = argv[2];
	string T1, T2, setOp;
	Expression exp = readQuery(argv[3], T1, T2, setOp);
	DEBUG_INSTR(exp.displayPostfix());
	RCSetOperator mySetOperator(new Relation(T1, pathT1, T1 == index), new Relation(T2, pathT2, T2 == index), exp);
	// Setting the path for saving results
	Generics::savePath = setOp;

    // Executing our binary operation
	mySetOperator.binaryOperation(setOp);


	return 0;
}
