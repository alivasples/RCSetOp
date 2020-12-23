#include <iostream>
#include <algorithm>
#include <regex>
#include <cctype>
#include <string>
#include <vector>
#include <queue>
#include <stack>
using namespace std;


string LST_OPERATORS[] = {"*","/","+","-","<=",">=","<",">","=","NOT","AND","OR"};
enum EN_OPERATORS{MULT, DIVIDE, PLUS, DIFF, LEQ, GEQ, LT, GT, EQ, NOT, AND, OR};
int NR_OPERATORS = 12;

/** Remeber: -1: greater precedence, 0: same precedence, 1: lower precedence */
int PRECEDENCES[12][12] = {
	{ 0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1},
	{ 0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1},
	{-1, -1,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1},
	{-1, -1,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1},
	{-1, -1, -1, -1,  0,  0,  0,  0,  0,  1,  1,  1},
	{-1, -1, -1, -1,  0,  0,  0,  0,  0,  1,  1,  1},
	{-1, -1, -1, -1,  0,  0,  0,  0,  0,  1,  1,  1},
	{-1, -1, -1, -1,  0,  0,  0,  0,  0,  1,  1,  1},
	{-1, -1, -1, -1,  0,  0,  0,  0,  0,  1,  1,  1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1,  0,  1,  1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0,  1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0}
};

string ST_OPERATOR_ARITH = "\\*|/|\\+|-";
string ST_OPERATOR_LOGIC = "<=|>=|<|>|=";
string ST_OPERATOR_NEGAT = "NOT";
string ST_OPERATOR_CONNE = "AND|OR";
string ST_OPERATOR = ST_OPERATOR_ARITH + "|" + ST_OPERATOR_LOGIC + "|" + ST_OPERATOR_NEGAT + "|" + ST_OPERATOR_CONNE;
string ST_BRACKETS = "\\(|\\)";
string ST_OPERAND = "\\d+(\\.\\d+)?|\\w+\\.\\w+";
string ST_TOKENS = ST_OPERATOR + "|" + ST_BRACKETS + "|" + ST_OPERAND;

regex REG_OPERATOR_ARITH(ST_OPERATOR_ARITH);
regex REG_OPERATOR_LOGIC(ST_OPERATOR_LOGIC);
regex REG_OPERATOR_NEGAT(ST_OPERATOR_NEGAT);
regex REG_OPERATOR_CONNE(ST_OPERATOR_CONNE);
regex REG_OPERATOR(ST_OPERATOR);
regex REG_BRACKETS(ST_BRACKETS);
regex REG_OPERAND(ST_OPERAND);
regex REG_TOKENS(ST_TOKENS);

/** This method compare two operators precedence.
  * It returns:
  *    1 if first operator has greater precedence
  *    0 if both operators has same precedence
  *   -1 if first operator has lower precedence
  *   -2 if op1 or op2 are not operators 
*/
// int cmpPrecedence(const string &op1, const string &op2){
// 	// Default validation: If op1 or op2 are invalid operators
// 	if(!(regex_match(op1, REG_OPERATOR) and regex_match(op2, REG_OPERATOR)))
// 		return -2;

// 	// When first operator is an arithmetic operator
// 	if(regex_match(op1, REG_OPERATOR_ARITH)){
// 		// When second operator is an arithmetic operator
// 		if(regex_match(op2, REG_OPERATOR_ARITH)){

// 		}
// 		return 1;
// 	}
// 	// When first operator is a logic operator
// 	else if(regex_match(op1, REG_OPERATOR_LOGIC)){
// 		// When second operator is an arithmetic operator
// 		if(regex_match(op2, REG_OPERATOR_ARITH)){

// 		}
// 		// When second operator is a logic operator
// 		else if(regex_match(op2, REG_OPERATOR_LOGIC)){
			
// 		}
// 		// When second operator is a logic connector
// 		else if(regex_match(op2, REG_OPERATOR_CONNE)){
			
// 		}
// 	}
// 	// When first operator is a negation
// 	else if(regex_match(op1, ST_OPERATOR_NEGAT)){
// 		// When second operator is an arithmetic operator
// 		if(regex_match(op2, REG_OPERATOR_ARITH)){

// 		}
// 		// When second operator is a logic operator
// 		else if(regex_match(op2, REG_OPERATOR_LOGIC)){
			
// 		}
// 		// When second operator is a logic connector
// 		else if(regex_match(op2, REG_OPERATOR_CONNE)){
			
// 		}
// 	}
// 	// When first operator is a logic connector
// 	else if(regex_match(op1, REG_OPERATOR_CONNE)){
// 		// When second operator is an arithmetic operator
// 		if(regex_match(op2, REG_OPERATOR_ARITH)){

// 		}
// 		// When second operator is a logic operator
// 		else if(regex_match(op2, REG_OPERATOR_LOGIC)){
			
// 		}
// 		// When second operator is a logic connector
// 		else if(regex_match(op2, REG_OPERATOR_CONNE)){
			
// 		}
// 	}
// }


/** This method returns the index of an element in an array */
int indexOf(string item, string array[], int size){
	for(int i = 0; i < size; i++){
		if(array[i] == item) return i;
	}
	return -1;
}

/** This method compare two operators precedence.
  * It returns:
  *    1 if first operator has greater precedence
  *    0 if both operators has same precedence
  *   -1 if first operator has lower precedence
  *   -2 if op1 or op2 are not operators 
*/
int cmpPrecedence(const string &op1, const string &op2){
	int idx1 = indexOf(op1, LST_OPERATORS, NR_OPERATORS);
	int idx2 = indexOf(op2, LST_OPERATORS, NR_OPERATORS);
	if(idx1 < 0 or idx2 < 0) return -2;
	return PRECEDENCES[idx1][idx2];
}

/** This method receives a string and a regular expression.
  * Its objective is to return a vector of all tokens 
  * that match the regular expression.
*/
vector<string> tokenize(const string &str, string reg) {
	// Variables definition
	vector<string> tokens;
	regex rgx (reg);
	sregex_token_iterator iter(str.begin(), str.end(), rgx, {/*-1, */0});
	sregex_token_iterator end;

	// Add all tokens to the vector of tokens
	while (iter != end)  {
		tokens.push_back(*iter);
		++iter;
	}

	// Return the vector of tokens
	return tokens;
}

/** This method receives a list of tokens for an infix expression
  * and transforms it into a postfix expression.
*/
queue<string> getPostfixExpression(vector<string> tokens){
	// Variables definition
	stack<string> pendingOps;
	queue<string> expression;
	regex regOperator();
	string nextOp;

	// Step 1: Add "(" to the pending operations stack
	pendingOps.push("(");
	// Step 2: Add ")" to the end of the expression
	tokens.push_back(")");

	// Step 3: For each token in the infix expression
	for(const string & token : tokens){
		// if token is an operand
		if(regex_match(token, REG_OPERAND)){
			expression.push(token);
		}
		// if token is "("
		else if(token == "("){
			pendingOps.push(token);	
		}
		// if token is ")"
		else if(token == ")"){
			// Get next operation from our pending operations
			string nextOp = pendingOps.top();
			pendingOps.pop();
			// Send next operations to the expression until a "(" is found
			while(nextOp != "("){
				expression.push(nextOp);
				// get next operation
				nextOp = pendingOps.top();
				pendingOps.pop();
			}
		}
		// if token is an operator
		else if(regex_match(token, REG_OPERATOR)){
			// send all operations in our stack of next operations to our expression,
			// while they have greater or equal precedence than the current one
			while(!pendingOps.empty() and regex_match(pendingOps.top(), REG_OPERATOR) and cmpPrecedence(pendingOps.top(), token) >= 0){
				// add the top of pending operations to the expression and pop it
				expression.push(pendingOps.top());
				pendingOps.pop();
			}
			// add the current operation to the stack of pending operations
			pendingOps.push(token);
		}
	}

	// Return the expression in postfix notation
	return expression;
}

int main(){
	string query = "DP.Category = SP.Category   AND DP.Product  = SP.Product    AND  (DP.Units <= SP.Units      AND  \nNOT (DP.Price < SP.Price) OR\nDP.Price >= SP.Price * 0.5) ";
	transform(query.begin(), query.end(), query.begin(), ::toupper);

	vector<string> tokens = tokenize(query, ST_TOKENS);
	queue<string> postifx = getPostfixExpression(tokens);

	while(!postifx.empty()){
		cout << postifx.front() << endl;
		postifx.pop();
	}

	return 0;
}