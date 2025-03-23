/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rpn.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:52:29 by okapshai          #+#    #+#             */
/*   Updated: 2025/03/23 16:55:35 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

// ----------------------------------------------------------------------------
// ---------------------------------------------------------------- Constructor
// ----------------------------------------------------------------------------
RPN::RPN() : _result(0), _stack() {
	if (DEBUG)
		std::cout << LGREEN << "RPN default constructor called." << RESET << std::endl;
}

RPN::RPN(RPN const & src) : _result(src._result), _stack(src._stack) {
	if (DEBUG)
		std::cout << LGREEN << "RPN copy constructor called." << RESET << std::endl;
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------- Destructor
// ----------------------------------------------------------------------------

RPN::~RPN() {
	if (DEBUG)
		std::cout << LRED << "RPN destructor called." << RESET << std::endl;
}

// ----------------------------------------------------------------------------
// --------------------------------------------------------------------- Getter
// ----------------------------------------------------------------------------

int const& RPN::getResult(void) const {
	return (this->_result);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------- Exceptions
// ----------------------------------------------------------------------------

const char* DivisionByZeroException::what() const throw() {
	return ("cannot divide by zero");
}

const char* NotEnoughNumbersException::what() const throw()  {
	return ("not enough number on stack");
}

const char* TooMuchNumbersException::what() const throw() {
	return ("too much numbers in expression");
}

const char* WrongInputException::what() const throw() {
	return ("rpn takes number <10 nb signs +-*/%");
}

// ----------------------------------------------------------------------------
// ------------------------------------------------------------------- Overload
// ----------------------------------------------------------------------------
RPN& RPN::operator=(RPN const& rhs) {
	if (DEBUG)
		std::cout << LBLUE << "RPN assignment operator called." << RESET << std::endl;

	this->_result = rhs._result;
	this->_stack = rhs._stack;

	return *this;
}

// ----------------------------------------------------------------------------
// -------------------------------------------------------------------- Methods
// ----------------------------------------------------------------------------

void RPN::doOperation(char op, int firstNb, int secondNb) {

	int result = 0;

	if (op == '+')
		result = firstNb + secondNb;

	else if (op == '-')
		result = firstNb - secondNb;

	else if (op == '*')
		result = firstNb * secondNb;

	else if (op == '/')
	{
		if (secondNb == 0)
			throw(DivisionByZeroException());
		result = firstNb / secondNb;
	}

	this->_stack.push(result);
}

bool RPN::isOperator(char c) {

	if (c == '-' || c == '+' || c == '/' || c == '*')
		return (true);

	return (false);
}


void RPN::readAndCalculate(std::string input) {

    //Loop through the input string: The function iterates over each character in the input string.
	for (int i = 0; i < (int)input.size(); i++) {

        //Skip spaces: It skips spaces to find numbers or operators.
		while (input[i] && input[i] == ' ')
			i++;

        //Check for digits: When it encounters a digit, it converts the character to an integer
        //(subtracting the ASCII value of '0' from the character's ASCII value) and pushes it onto the stack.
		if (isdigit(input[i]) != 0) {
			int nb = input[i] - '0';
			this->_stack.push(nb);
		}

        //Check for operators: If the character is an operator, the function performs several steps:
        //It first checks if there are at least two numbers on the stack, as an operator in RPN requires two operands.
        //If not, it throws a NotEnoughNumbersException.
		else if (isOperator(input[i]) == true) {
			if (this->_stack.size() < 2)
				throw (NotEnoughNumbersException());

            //It then pops the top two numbers from the stack
			int secondNb = this->_stack.top();
			this->_stack.pop();

			int firstNb = this->_stack.top();
			this->_stack.pop();

            //It calls doOperation, passing the operator and the two operands.
			doOperation(input[i], firstNb, secondNb);
		}
	}

    //Final result: After processing all characters in the input string, the final result of the expression
    //is expected to be the only number left on the stack.
    //The function assigns this number to _result and then pops it from the stack.
	this->_result = this->_stack.top();
	this->_stack.pop();

    //check if the stack is not empty,
    //which would indicate that there are too many numbers and not enough operators
    //in the input expression, leading to an unresolvable situation. In this case, it throws a TooMuchNumbersException.
	if (this->_stack.size() != 0)
		throw TooMuchNumbersException();
}

void RPN::parseInput(std::string input) {

    // loop through each character
	for (int i = 0; i < (int)input.size(); i++) {

        // check for valid characters
		if (isdigit(input[i]) == 0 && isOperator(input[i]) == false && input[i] != ' ')
			throw(WrongInputException());

        // check for digit followd directly by another character
		if (isdigit(input[i]) != 0 && input[i + 1] && input[i + 1] != ' ')
			throw(WrongInputException());

        // check for operator followd directly by another character
		if (isOperator(input[i]) && input[i + 1] && input[i + 1] != ' ')
			throw(WrongInputException());
	}
}