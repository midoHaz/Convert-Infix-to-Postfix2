/*
* Team 11
* 
* description:-
*		This program is to convert infix to postfix and handle all cases about it.
* 
*Assignment 01
* 
*we will include library iostream ,string , algorithm
*
*/
#include<iostream>
#include<string>
#include<algorithm>
#define max_size 100
using namespace std;
/*
* we define the templete class instead making class overload so we can make any number of stacks with differend types
*/
template<class T>
/*	#####First we make a class stack with data members#####:-
* 1-int top to point to the top of the stack
* 2-arr to carry the numbers in the stack and we give it data type T to change it if we want to avoid class overloading
*
*/
class Stack {
private:
	int top;
	T arr[max_size];
	string pos, inf = "";
public:
	/*
	* 1- constructor to intal top and make it equal to -1
	*/
	Stack() {
		top = -1;
	}
	/*
	*	2- push()function with return type void  and a parameter with data type'T'
	*	=> this function add elements to the stack from one direction inside it we first check if the stack is full
	*		if true print'This is invalid expression' else we raise top with 1 and add the next element to the stack
	*/
	void push(T item) {
		if (isFull()) {
			cout << "\t\t *****This is invalid expression***** \t\t\n" << endl;
		}
		arr[++top] = item;
	}
	/*
	3- pop()function with return type 'T' to change it to any data type instead of class overload
	*=> this function delete elements from the stack from one direction
	 we declare variable item and store (arr[top]) in it then reduce top with 1 and return the remaining elements in the stack
	*/
	T pop() {
		T item = arr[top];
		top--;
		return item;
	}
	/*
	4- peak()function with return type 'T' to change it to any data type instead of class overload
	*=> this function return element of  top
	*/
	T peak() {
		return arr[top];
	}
	/*
	5- is Full function to test if function is full
	*/
	bool isFull() {
		if (top == max_size - 1)
			return true;
		return false;
	}
	/*
		6- is Empty function to test if function is Empty
	*/
	bool isEmpty() {
		if (top == -1)
			return true;
		return false;
	}
	/*
	fun display that display elements inside the stack
	*/
	void display() {
		for (int i = 0; i <= max_size - 1; i++) {
			cout << arr[i] << "  ";
		}
	}
	/*this function to return the size of the stack*/
	int size() {
		return top + 1;
	}
};
/*
* bool function with parametar char to check
 infix is operand or not .It will be valid if it is(0:9_a:z_A:Z)
*/
bool isOperand(char oper)
{
	return ('0' <= oper && oper <= '9') ||
		('a' <= oper && oper <= 'z') ||
		('A' <= oper && oper <= 'Z');
}
/*
* bool function with parametar char to check
 infix is operator or not .It will be valid if it is (+_-_*_/_%_^_(_))
*/
bool isOperator(char oper)
{
	return oper == '+' || oper == '-' ||
		oper == '*' || oper == '/' || oper == '%' ||
		oper == '^' || oper == ')' || oper == '(';
}
/*
* int function with parametar char to check
* the periority of operator which is orderd acoordingn to (_ "+_-" _ "*_/_%" _^
*/
int perc(char per) {
	if (per == '(')
		return -1;
	if (per == '+' || per == '-')
		return 1;
	if (per == '*' || per == '/' || per == '%')
		return 2;
	if (per == '^')
		return 3;
}
void main() {
	/* two object char_int and three variable string(infix_postix_temp)
	and three variable int (result_op01_op02 */
a:	Stack<int> operandST;
	Stack <char> operatorST;
	string infix, postfix, temp = " ";
	int result, op01=0, op02=0;
	cout << "\n\n\t\t ************************************************";
	cout << "\n\t\t *****please enter infix expression: ";
	/*to ask user to enter infix expression and check if infix =="" print '* ****This is invalid expression * ****'
		then ask user if he want to enter another expression or not  else do the following instructions */
	getline(cin, infix);
	if (infix == "") {
		cout << "\t\t * ****This is invalid expression * ****\t\t\n" << endl;
		goto b;
	}
	else {
		cout << "\n\n\t\t ***** infix expression   : " << infix << "\t\t\n\n";
		/*Push "(" onto stack to avoid uderflow ,
		and add ")" to the end of infix to pop stack elements until reach "("
		*/
		infix += ')';
		operatorST.push('(');
		/* for loop to convert infix expression to postfix expression*/
		for (int i = 0; i < infix.length(); i++)
		{
			/* if there is space continue */
			if (infix[i] == ' ')
			{
				continue;
			}
			/* if there is operand add operand to postfix and check while the operand and the following
				is operand(multiDigit) add them to postfix and increament i by 1*/
			if (isOperand(infix[i])) {
				postfix += infix[i];
				while (isOperand(infix[i]) && isOperand(infix[i + 1])) {
					i++;
					postfix += infix[i];
				}
			}
			/* else if(outer statement) there is operator :-
			1) add ','to postfix between every element
			2)if "(" push into opertorSt (inner statement)
			3)else if ")" while top of the stack not equal "("
			check if the operatorStack is empty if true
			print('this is invalid expression') and ask user if he want to enter another expression or not
			 else pop from the stack and add to the postfix (inner statement)
			4)else if any other operator check if infix expression periority is less than or
			equal operator in the top of the stack , pop the operator from the stack add to postfix
			pop from the stack and add to the postfix
			else infix expression periority is greater than or equal operator in the top of the stack push in the stack (inner statement)
			*/
			else if (isOperator(infix[i])) {
				postfix += ',';
				// 1 (
				if (infix[i] == '(')
				{
					operatorST.push('(');
				}
				else if (infix[i] == ')') {
					while (operatorST.peak() != '(') {
						if (operatorST.isEmpty()) {
							cout << "\t\t*****This is invalid expression*****\n";
							goto b;
						}
						else
							postfix += operatorST.pop();
					}
					operatorST.pop();
				}
				else {
					while (perc(infix[i]) <= perc(operatorST.peak())) {
						postfix += operatorST.pop();
					}
					operatorST.push(infix[i]);
				}
			}
			/* if there is any other operator or operand print This is invalid expression
			then goto b to ask user if he wants to enter another expression
			*/

			else {
				cout << "\t\t ***** This is invalid expression ***** \t\t" << endl;
				goto b;
			}

		}
		/* to print postfix expression*/
		cout << "\t\t ***** Postfix expression : " << postfix << "\t\t\n\n";
		/* for loop to evluate postfix expresssion */
		for (int i = 0; i < postfix.length(); i++) {
			/* check if the postfix is alpha (from library algorithm) if true print 'Expression does not need to be evaluated'
			then  ask user if he wants to enter another expression
			*/
			if (isalpha(postfix[i]))
			{
				cout << "\t\t *****Expression does not need to be evaluated***** \t\t\n";
				goto b;
			}
			/*check if the postfix is operator then check:-
			1)if size of stack is less than 2 print 'Invalid expression'
			then  ask user if he wants to enter another expression
			2)else pop last 2 operand from the stack  and calculate the value of expression according to the operator (using swith case statement)then push the result to the operand stack
			*/

			if (isOperator(postfix[i])) {
				if (operandST.size() < 2) {
					cout << "\t\t *****Invalid Expression***** \t\t\n";
					goto b;
				}
				op02 = operandST.pop();
				op01 = operandST.pop();
				switch (postfix[i]) {
				case '+':
					operandST.push(op01 + op02);
					break;
				case '-':
					operandST.push(op01 - op02);
					break;
				case '*':
					operandST.push(op01 * op02);
					break;
				case '/':
					if (op02 == 0) {
						cout << "\t\t *****This is invalid expression***** \t\t\n";
						goto b;
					}
					operandST.push(op01 / op02);
					break;
				case '%':
					operandST.push(op01 % op02);
					break;
				}

			}
			/*
			* this function is case of multidigit:-
			first we initiate temp with empty quotation
			second use ( do while loop )to check if the element in the postfix expression is operand
			and not equal ',' then store it in temp and increament i by 1
			finally push temp to operandST after convert it from string to int (using stoi function )
			*/
			if (isOperand(postfix[i])) {
				temp = "";
				do {
					temp += postfix[i];
					i++;
				} while (isOperand(postfix[i]) && isOperand(postfix[i]) != ',');
				operandST.push(stoi(temp));
			}
		}
		/*
		* we store the final (remaining) value in the stack into variable result
		*/
		result = operandST.pop();
		cout << "\t\t ***** Evaluation value   : " << result << "\t\t\n";
		/* ask user if he want to enter another expression if y/Y repeat the previous instruction
		if n/N exit from the program*/
	}
	b:	char x;
		cout << "\n\t\t ************************************************";
		cout << "\n\n\t\t *****Do you want try another expresion (y/n) :  ";
		cin >> x;
		if (x == 'y' || x == 'Y')
		{
			getline(cin, infix);
			goto a;
			system("pause");

		}
		else if (x == 'n' || x == 'N')
		{
			cout << "\t\t ###########---------Thank you for your time --------########### \t\t" << endl;
			system("pause");
		}
}	