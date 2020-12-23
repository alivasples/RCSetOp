//============================================================================
// Name        : RelCondSetOps.cpp
// Author      : alivasples
// Version     : 1.0
// Description : Program to perform the Relational Conditional Set Operations
//============================================================================

#include <iostream>
#include <Expression.h>
using namespace std;

int main() {
	string query = "DP.Category = SP.Category   AND DP.Product  = SP.Product    AND  (DP.Units <= SP.Units      AND  \nNOT (DP.Price < SP.Price) OR\nDP.Price >= SP.Price * 0.5) ";
	Expression exp(query);
	for(string s : exp.getPostfixVtr()){
		cout << s << endl;
	}
	return 0;
}
