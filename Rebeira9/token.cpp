// This file contains the specification for the token class.  
#include <cmath>
#include <cassert>
#include <cctype>
#include "token.h"
/*
{
      static bool unary; // to identify unary minus
      bool isnumber;     // identify whether it's a number or not
      double value;      // an operand
      char ch;           // an operator or parenthesis
      bool valid;        // true if Token is valid
}
*/
Token::      Token()                         // no argument constructor
{
	valid=false;
};

Token::      Token(double d)                   // double constructor
{
	value = d;
	valid=true;
	isnumber = true;
};
Token::      Token(int i)                      // int constructor
{
	value = i;
	valid = true;
	isnumber = true;
};
Token::      Token(char c)                     // char constructor
{
	ch = c;
	isnumber = false;
	switch (ch) {
		case '(': 
		case ')': 
		case '+': 
		case '-': 
		case '*': 
		case '/': 
		case '%': 
		case '^':
		case '#':	
			valid = true;
			return;
		default:
			valid = false;
	};
};

bool Token::      Valid() const              // true if token is valid
{return valid;};
bool Token::      IsOperand() const          // true if token is an operand
{return isnumber;};
bool Token::      IsOperator() const         // true if token is an operator
{
	switch(ch) {
		case '+':
		case '-':
		case '*':
		case '/':
		case '%':
		case '^':
			return true;
		default:
			return false;
	};
};
bool Token::      IsLeftParen() const        // true if token is a (
{
	return (ch == '(');
};
bool Token::      IsRightParen() const       // true if token is a )
{
	return (ch == ')');
};
double Token::      Operand() const          // returns the value of the operand
{
	return value;
};
char Token::      Operator() const           // returns '+' '-' '*' '/' '%' '^' 
{
	return ch;
};
int Token::      Precedence() const          // returns precedence of operator
{
	switch(ch) {
		case '(': return 0;
		case ')': return 0;
		case '^': return 3;
		case '*': return 2;
		case '/': return 2;
		case '%': return 2;
		case '+': return 1;
		case '-': return 1;
		case '#': return 9;
		default: return 0;
	};
};

Token Token::      operator + (const Token & arg) const // add Token to object
{
	return Token(value + arg.value);
};
Token Token::      operator - (const Token& arg) const // subtract Token from object
{
	return Token(value - arg.value);
};
Token Token::      operator * (const Token& arg) const // multiply object by Token
{
	return Token(value * arg.value);
};
Token Token::      operator / (const Token& arg) const // divide object by Token
{
	return Token(value / arg.value);
};
Token Token::      operator % (const Token& arg) const // modulus object by Token
{
	return Token(int(value) % int(arg.value));
};
Token Token::      operator ^ (const Token& arg) const // raise object to power of Token
{
	return Token(pow(value,arg.value));
};
istream& operator >> (istream&i,Token&t) // overload input
{
	char c;
	i.get(c);
	if (isdigit(c)) {
		i.putback(c);
		int v;
		i >> v;
		t = Token(v);
	} else {
		t = Token(c);
	};
	return i;
};
         // A friend function is a none member function that is given access
         // to the private members of a class. Friend functions should be
         // avoided if possible.
         // The >> operator will skip blanks and tabs, not '\n'.
         // '\n' will be read and the token is not valid.
         // This provides a way to have a loop read one line of tokens 
         // then exit when '\n is read.


ostream& operator << (ostream&o,const Token&t) //overload output
{
	assert(t.Valid());
	if (t.IsOperand()) {
		o << t.Operand();
	} else {
		o << t.Operator();
	};
	return o;
};