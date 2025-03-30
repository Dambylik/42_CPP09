/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:51:34 by okapshai          #+#    #+#             */
/*   Updated: 2025/03/30 20:56:15 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Colors.hpp"
#include <iostream>

class CsvFailToOpen : public std::exception 
{
	public:
		virtual const char* what() const throw() {
			return ("Error: could not open csv database file.");
		}
};

class InputFail : public std::exception 
{
	public:
		virtual const char* what() const throw() {
			return ("Error: input file is corrupted.");
		}
};

// class WrongInputFile : public std::exception 
// {
// 	public:
// 		virtual const char* what() const throw() {
// 			return ("Error: Wrong input file");
// 		}
// };

// class WrongArg : public std::exception 
// {
// 	public:
// 		virtual const char* what() const throw() {
// 			return ("This program only runs with 2 arguments.");
// 		}
// };

class NoData : public std::exception 
{
	public:
		virtual const char* what() const throw() {
			return ("No valid entries found in database file");
		}
};

class InvalidHeader : public std::exception 
{
	public:
		virtual const char* what() const throw() {
			return ("Error: invalid file header.");
		}
};

class DataError : public std::exception 
{
	public:
		virtual const char* what() const throw() {
			return (" <= Error: Invalid database format.");
		}
};

class DateError : public std::exception 
{
	public:
		virtual const char* what() const throw() {
			return (" <= Error: Invalid date in database.");
		}
};

class InvalidRate : public std::exception 
{
	public:
		virtual const char* what() const throw() {
			return (" <= Error: Invalid exchange rate.");
		}
};
