/*
 *  Created by alivasples 2020 - December
 */

#ifndef RCSETOPERATOR_H_
#define RCSETOPERATOR_H_

#include <iostream>
#include <string>
#include <vector>

#include <IndexTree.h>
#include <Relation.h>
#include <Expression.h>

using namespace std;

enum SET_OPERATOR{ SET_UNION, SET_INTERSECTION, SET_DIFFERENCE, SET_SUBSET};

class RCSetOperator{
	private:
		// ATTRIBUTES
		Relation *myT1;
		Relation *myT2;
		Expression exp; // query expression

	public:
		// METHODS
		/** Default Constructor */
		RCSetOperator() {};

		/** Parameterized Constructor */
		RCSetOperator(Relation *T1, Relation *T2, Expression exp);

		/** Method that computes the result of the expression for a table and a tuple */
		bitset<MAX_TUPLES> indexTupleQuery(Relation *T, Relation *tuple);

		/** This method performs the union, intersection or union of two relations */
		bitset<MAX_TUPLES> binaryOperation(Relation *T1, Relation *T2, SET_OPERATOR setOP, bool show = true);
		void binaryOperation(const string &setOP, bool show = true);

		/** This method returns true if T1 is subset of T2, false if not */
		bool isSubset();

		/**This method returns true if the first tuple (should be the only tuple) in the right relation
		 * is member of the left relation, false if not */
		bool isMember(Relation *T1, Relation *T2);

		/** This method tests for each tuple of T2 if is conditional member of T1 */
		void showAllMembers(Relation *T1, Relation *T2);
};

/** Parameterized Constructor */
RCSetOperator::RCSetOperator(Relation *T1, Relation *T2, Expression exp){
	this->myT1 = T1;
	this->myT2 = T2;
	this->exp = exp;
}

/** Method that computes the result of the expression for a table and a tuple */
bitset<MAX_TUPLES> RCSetOperator::indexTupleQuery(Relation *T, Relation *tuple){
	// Variables definition
	stack<bitset<MAX_TUPLES>> subresults;
	stack<string> nextOperands;
	string tableName = T->getName();
	string tupleName = tuple->getName();
	string attrName;
	string value;
	string operandR, operandL, cmp;

	// Read the expression token by token
	for(string token : exp.getPostfixVtr()){
		// If token refers to a column of T
		if(token.substr(0, min((int)token.size(),(int)tableName.size())) == tableName){
			nextOperands.push(token);
		}
		// If token refers to a column of tuple
		else if(token.substr(0, min((int)token.size(),(int)tupleName.size())) == tupleName){
			// Get the name of the attribute
			attrName = token.substr(tupleName.size()+1);
			// Get the value of the attribute in the current tuple
			value = tuple->getCurrentAttrValue(attrName);
			// Push it into the stack of next operands
			nextOperands.push(value);
		}
		// If token is a constant operand
		else if(regex_match(token, REG_OPERAND)){
			nextOperands.push(token);
		}
		// If token is an arithmetic operator
		else if(regex_match(token, REG_OPERATOR_ARITH)){
			// Pop the last two operands from the stack
			float valR = stof(nextOperands.top());
			nextOperands.pop();
			float valL = stof(nextOperands.top());
			nextOperands.pop();
			// compute the result
			float result;
			if(token == "+") result = valL + valR;
			else if(token == "-") result = valL - valR;
			else if(token == "*") result = valL * valR;
			else if(token == "/") result = valL / valR;
			else ERROR_MSG("Operation " + token + " unknown.");
			// push the value in the next operands
			nextOperands.push(to_string(result));
		}
		// If token is a logical operator
		else if(regex_match(token, REG_OPERATOR_LOGIC)){
			// Get the value to compare
			operandR = nextOperands.top();
			nextOperands.pop();
			// Get the attribute name of the table
			operandL = nextOperands.top();
			// When the left operand is the Table.Column
			if(operandL.substr(0, min((int)operandL.size(),(int)tableName.size())) == tableName){
				attrName = operandL.substr((int)tableName.size() + 1);
				value = operandR;
				cmp = token;
			}
			// When the right operand is the Table.Column
			else{
				attrName = operandR.substr((int)tableName.size() + 1);
				value = operandL;
				cmp = REV_OPERATORS.at(token);
			}

			subresults.push(T->indexQuery(attrName, cmp, value));
		}
		// If token is a negation
		else if(regex_match(token, REG_OPERATOR_NEGAT)){
			// negate the last value
			subresults.top().flip();
		}
		// If token is a logical connector
		else if(regex_match(token, REG_OPERATOR_CONNE)){
			// Get the last 2 subresults
			bitset<MAX_TUPLES> valR = subresults.top();
			subresults.pop();
			bitset<MAX_TUPLES> valL = subresults.top();
			subresults.pop();
			// Compute the result and push it again
			if(token == "AND") subresults.push(valL & valR);
			else if(token == "OR") subresults.push(valL | valR);
			else ERROR_MSG(token + " operation is not supported");
		}
		// any other token would be an error
		else{
			ERROR_MSG("Token \"" << token << "\" not recognized!");
		}
	}

	DEBUG_MSG("SUBRESULT: " << subresults.top() << endl << endl);
	// Return the result
	return subresults.top();
}

/** This method performs the union, intersection or union of two relations */
bitset<MAX_TUPLES> RCSetOperator::binaryOperation(Relation *T1, Relation *T2, SET_OPERATOR setOp, bool show){
	// Variables definition
	bitset<MAX_TUPLES> resultT1; // all bits are 0's by default
	bitset<MAX_TUPLES> resultT2; // all bits are 0's by default

	// When set operations is difference or union, initialize R1 with 1's (valid tuples)
	if(setOp == SET_DIFFERENCE or setOp == SET_UNION){
		resultT1.set(); // all to 1's
	}

	if(T1->hasIndex()){
		int idTuple = 0;
		while(T2->nextLine()){
			// Find the result for the current tuple
			// (Remember that internally T2 keeps a pointer to its current tuple)
			bitset<MAX_TUPLES> subresult = indexTupleQuery(T1, T2);
			// Update our result according to the set operator
			switch(setOp){
			case SET_INTERSECTION:
				resultT1 = resultT1 | subresult;
				break;
			case SET_DIFFERENCE:
				resultT1 = resultT1 & ~subresult;
				break;
			case SET_UNION:
				if(subresult.none()) resultT2.set(idTuple);
				break;
			default: ERROR_MSG("Operator not supported"); break;
			}
			idTuple++;
		}
	}
	else{
		ERROR_MSG("Operation not supported. The left Relation must be the one which contains the index.");
	}
	// if show is true then show all valid tuples
	if(show){
		DEBUG_MSG("T1: " << resultT1 << endl);
		int sizeResultT1 = T1->displayTuples(resultT1);
		DEBUG_MSG("T2: " << resultT2 << endl);
		int sizeResultT2 = T2->displayTuples(resultT2);
		cout << "\nNumber of tuples in result: " << sizeResultT1 + sizeResultT2 << " tuples.\n";
		Generics::saveMessage(sizeResultT1 + sizeResultT2, "size");
	}

	// Return the bitset of valid tuples
	return resultT1;
}



/** This method performs the union, intersection or union of two relations */
void RCSetOperator::binaryOperation(const string &setOp, bool show){

    // Start time for execution time
    clock_t start;
    double duration;
    start = clock();

	if(setOp == "UNION") binaryOperation(myT1, myT2, SET_UNION, show);
	else if(setOp == "INTERSECT" or setOp == "INTERSECTION") binaryOperation(myT1, myT2, SET_INTERSECTION, show);
	else if(setOp == "DIFFERENCE" or setOp == "DIFF" or setOp == "MINUS") binaryOperation(myT1, myT2, SET_DIFFERENCE, show);
	else if(setOp == "SUBSET" or setOp == "BELONG" or setOp == "IN") cout << isSubset() << endl;
	else if(setOp == "CONTAINS" or setOp == "INCLUDES") isMember(myT1, myT2);
	else if(setOp == "CONTAINSEACH" or setOp == "INCLUDESEACH") showAllMembers(myT1, myT2);
	else ERROR_MSG("Operation " + setOp + " is not recognized");

	// Calculating the duration of the program execution
	duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
	// Show and save the execution time
	if(setOp == "CONTAINSEACH" or setOp == "INCLUDESEACH"){
		cout << "\nDuration AVG per member: "<< duration/myT2->size() << " seconds.\n";
		cout << "\nTotal Duration: "<< duration << " seconds.\n";
		Generics::saveMessage(duration/myT2->size(), "time");
	}
	else{
		cout << "\nDuration: "<< duration << " seconds.\n";
		Generics::saveMessage(duration, "time");
	}
}


/** This method returns true if T1 is subset of T2, false if not */
bool RCSetOperator::isSubset(){
	// Perform the intersection operation
	bitset<MAX_TUPLES> intersection = binaryOperation(myT1, myT2, SET_INTERSECTION, false);
	// If any of the tuples of T1 is not on the intersection, then T1 is not subset of T2
	for(int i = 0; i < myT1->size(); i++){
		if(!intersection.test(i)) return false;
	}
	// If all tuples of T1 were intersected, then it is a subset
	return true;
}


/** This method returns true if the first tuple (should be the only tuple) in the right relation
  * is member of the left relation, false if not */
bool RCSetOperator::isMember(Relation *T1, Relation *T2){
	// Variables definition
	bitset<MAX_TUPLES> result;

	// Only possible if T1 has index
	if(T1->hasIndex()){
		int idTuple = 0;
		// Read first tuple
		T2->nextLine();
		// Find the result for the current tuple
		result = indexTupleQuery(T1, T2);
	}
	else{
		ERROR_MSG("Operation not supported. The left Relation must be the one which contains the index.");
	}
	// If any of the tuples of T1 satisfies the condition, then the first tuple of T2 is conditional member of T1
	for(int i = 0; i < myT1->size(); i++){
		if(result.test(i)) return true;
	}
	// If none tuple from T1 satisfies the condition with the given tuple, that tuple is not conditional member of T1
	return false;
}


/** This method tests for each tuple of T2 if is conditional member of T1 */
void RCSetOperator::showAllMembers(Relation *T1, Relation *T2){
	for (int i = 0; i < T2->size(); i++){
		cout << isMember(T1, T2);
	}
}


#endif /* RCSETOPERATOR_H_ */
