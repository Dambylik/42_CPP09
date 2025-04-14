/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rpn.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:52:29 by okapshai          #+#    #+#             */
/*   Updated: 2025/04/14 12:05:10 by okapshai         ###   ########.fr       */
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

		if (isdigit(input[i]) != 0) {
			int nb = input[i] - '0';
			this->_stack.push(nb);
		}
		
		else if (isOperator(input[i]) == true) {
			if (this->_stack.size() < 2)
				throw (NotEnoughNumbersException());

            int secondNb = this->_stack.top();
			this->_stack.pop();

			int firstNb = this->_stack.top();
			this->_stack.pop();

			performCalculation(input[i], firstNb, secondNb);
		}
	}
	this->_result = this->_stack.top();
	this->_stack.pop();
	
	if (this->_stack.size() != 0)
		throw TooMuchNumbersException();
}

void RPN::processInput( std::string input ) {

	for (int i = 0; i < (int)input.size(); i++) {
		if (isdigit(input[i]) == 0 && isOperator(input[i]) == false && input[i] != ' ')
			throw(WrongInputException());

		if (isdigit(input[i]) != 0 && input[i + 1] && input[i + 1] != ' ')
			throw(WrongInputException());

		if (isOperator(input[i]) && input[i + 1] && input[i + 1] != ' ')
			throw(WrongInputException());
	}
}