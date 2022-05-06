/*
Ayesh Rebeira 
CSIS 352 
Assignment 1 
*/

#include "token.h"
#include "queueType.h"
#include "stackType.h"
#include <iostream>

using namespace std;

// function fwd declaration to display the postfix queue
void displayQueue(queueType<Token>);


int main()
{
	Token t;
	Token result;

	queueType <Token> aQueueToken;
	stackType <Token> aStackToken;


	cout << "\nEvaluating Infix to Postfix expression\n"
		<< "-----------=====----=======-----------\n";

	cout << "\nEnter a valid arithmetic expression on one line: ";
	cin >> t;
	while (t.Valid())
	{
		cout << "token: " << t << endl;
		if (t.IsOperand())
		{
			// adding operand to postfix queue
			aQueueToken.addQueue(t);
		}
		else if (t.IsOperator())
		{
			// adding operators to stack respecting the condition
			while (!aStackToken.isEmptyStack() && aStackToken.top().Precedence())
			{
				// add stack popped operators to the queue here
				aQueueToken.addQueue(aStackToken.top());
				aStackToken.pop();
			}
			aStackToken.push(t);

			// push if the precedence in stack is greater or equal to scanned token
			// otherwise pop the top and add top to queue then scanned token to stack
		}
		else if (t.IsLeftParen())
		{
			// push to stack the left parenthesis
			aStackToken.push(t);
		}
		else if (t.IsRightParen())
		{
			/*
			if correct paren then pop every top until '(' is found.
			 add every popped item to queue. but get rid of both () */

			while (!aStackToken.top().IsLeftParen())
			{
				// Pop stack right paren here and
				// add stack popped operators to queue
				aQueueToken.addQueue(aStackToken.top());
				aStackToken.pop();
			}
			// Pop stack leftparen here
			aStackToken.pop();

		}

		cin >> t;
	}

	// add remaining element from stack to the queue here
	while (!aStackToken.isEmptyStack())
	{
		aQueueToken.addQueue(aStackToken.top());
		aStackToken.pop();
	}

	cout << "The postfix will be: ";

	displayQueue(aQueueToken);

	//Evaluating the Postfix Expression//
	

	cout << "\nEvaluating the Postfix Expression\n"
		<< "---------------=======-----------\n";


	while (!aQueueToken.isEmptyQueue())
	{
		if (aQueueToken.front().IsOperand())
		{   // if the token is an operand,
		   // push it on the stack  
			aStackToken.push(aQueueToken.front());

			aQueueToken.deleteQueue();

		}
		else if (aQueueToken.front().IsOperator())
		{  // if the token is an operator, 
		   // pop the top two operands
		   // perform the arithmetic (taking care 
		   // that the operands are in the proper order)
		   // push the result
			if (aStackToken.top().IsOperand())
			{

				aStackToken.push(aQueueToken.front());
				aStackToken.pop();

				switch (aQueueToken.front().Operator())
				{
				case '+':  result = aStackToken.top() + aStackToken.top(); break;
				case '-':  result = aStackToken.top() - aStackToken.top(); break;
				case '*':  result = aStackToken.top() * aStackToken.top(); break;
				case '/':  result = aStackToken.top() / aStackToken.top(); break;
				case '%':  result = aStackToken.top() % aStackToken.top(); break;
				case '^':  result = aStackToken.top() ^ aStackToken.top(); break;
				}
			}
			aStackToken.push(result);
		}
		aQueueToken.deleteQueue();
	}

	cout << "Result = " << result << "\n";


	return 0;
}

// function to display the postfix queue
void displayQueue(queueType<Token> theQueue)
{
	while (!theQueue.isEmptyQueue())
	{
		cout << theQueue.front() << " ";
		theQueue.deleteQueue();
	}
	cout << "\n";
}