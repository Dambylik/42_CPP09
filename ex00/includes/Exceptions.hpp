/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:51:34 by okapshai          #+#    #+#             */
/*   Updated: 2025/03/31 15:45:06 by okapshai         ###   ########.fr       */
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

class InputFailToOpen : public std::exception 
{
	public:
		virtual const char* what() const throw() {
			return ("Error: could not open input file.");
		}
};

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
			return ("Update data file.");
		}
};

