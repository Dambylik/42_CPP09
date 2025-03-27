/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:51:34 by okapshai          #+#    #+#             */
/*   Updated: 2025/03/27 17:28:24 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Colors.hpp"
#include <iostream>

class CsvFail : public std::exception 
{
	public:
		virtual const char* what() const throw() {
			return ("Error: csv database is corrupted.");
		}
};

class WrongExtension : public std::exception 
{
	public:
		virtual const char* what() const throw() {
			return ("This program only runs with a .csv or .txt file.");
		}
};

class WrongArg : public std::exception 
{
	public:
		virtual const char* what() const throw() {
			return ("This program only runs with 2 arguments.");
		}
};

class NoData : public std::exception 
{
	public:
		virtual const char* what() const throw() {
			return ("You have a backup right? Just asking...");
		}
};

class InvalidHeader : public std::exception 
{
	public:
		virtual const char* what() const throw() {
			return ("Error: invalid file header.");
		}
};
