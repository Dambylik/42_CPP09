/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:51:34 by okapshai          #+#    #+#             */
/*   Updated: 2025/04/03 14:15:51 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>

class DivisionByZeroException : public std::exception 
{
	public:
		virtual const char* what() const throw() {
			return ("cannot divide by zero");
		}
};

class TooMuchNumbersException : public std::exception 
{
	public:
		virtual const char* what() const throw() {
			return ("too much numbers in expression");
		}
};

class NotEnoughNumbersException : public std::exception 
{
	public:
		virtual const char* what() const throw() {
			return ("not enough number on stack");
		}
};

class WrongInputException : public std::exception 
{
	public:
		virtual const char* what() const throw() {
			return ("rpn takes number <10 & signs +-*/%");
		}
};