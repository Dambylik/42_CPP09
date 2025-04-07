/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rpn.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:52:29 by okapshai          #+#    #+#             */
/*   Updated: 2025/04/03 14:47:34 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Rpn.hpp"

RPN::RPN() : _result(0), _stack() {}

RPN::RPN( RPN const & src ) : _result(src._result), _stack(src._stack) {}

int const & RPN::getResult( void ) const { return (this->_result);}

RPN & RPN::operator=( RPN const & other ) {
	
	this->_result = other._result;
	this->_stack = other._stack;
	return (*this);
}
RPN::~RPN() {}

//-------------------------------------------------------------------Methods

void RPN::performCalculation( char oper, int firstNb, int secondNb ) {

	int result = 0;

	if (oper == '+')
		result = firstNb + secondNb;

	else if (oper == '-')
		result = firstNb - secondNb;

	else if (oper == '*')
		result = firstNb * secondNb;

	else if (oper == '/')
	{
		if (secondNb == 0)
			throw(DivisionByZeroException());
		result = firstNb / secondNb;
	}

	this->_stack.push(result);
}

bool RPN::isOperator( char c ) {

	if (c == '-' || c == '+' || c == '/' || c == '*')
		return (true);
	return (false);
}

void RPN::calculateRpn( std::string input ) {

	for (int i = 0; i < (int)input.size(); i++) {
		
		while (input[i] && input[i] == ' ')
			i++;

		if (isdigit(input[i]) != 0) { // if = 0 -> not a digit, if = 1 -> digit
			int nb = input[i] - '0';
			this->_stack.push(nb);
		}
		
		else if (isOperator(input[i]) == true) {
			if (this->_stack.size() < 2) // Checks if there are at least two numbers on the stack
				throw (NotEnoughNumbersException());

            int secondNb = this->_stack.top(); // //It then pops the top two numbers from the stack
			this->_stack.pop();

			int firstNb = this->_stack.top();
			this->_stack.pop();

			performCalculation(input[i], firstNb, secondNb);
			//Final result: After processing all characters in the input string, the final result of the expression
    		//is expected to be the only number left on the stack.
		}
	}
	this->_result = this->_stack.top(); //The function assigns this number to _result and then pops it from the stack.
	this->_stack.pop();
	
	if (this->_stack.size() != 0)  //check if the stack is not empty,
		throw TooMuchNumbersException();
}

void RPN::processInput( std::string input ) {

	for (int i = 0; i < (int)input.size(); i++) { // Prevents "3 4 a +"
		if (isdigit(input[i]) == 0 && isOperator(input[i]) == false && input[i] != ' ')
			throw(WrongInputException());

		if (isdigit(input[i]) != 0 && input[i + 1] && input[i + 1] != ' ') // Prevents "34 +" (should be "3 4 +").
			throw(WrongInputException());

		if (isOperator(input[i]) && input[i + 1] && input[i + 1] != ' ') // //Prevents "3 4+ " (should be "3 4 +").
			throw(WrongInputException());
	}
}