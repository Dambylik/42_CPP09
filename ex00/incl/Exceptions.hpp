/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:51:34 by okapshai          #+#    #+#             */
/*   Updated: 2025/03/23 16:51:36 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

# include <iostream>

class ErrorException : public std::exception 
{
	public:
		virtual const char* what() const throw();
};

class FileOpeningException : public std::exception 
{
	public:
		virtual const char* what() const throw();
};
		
class ParseFailException : public std::exception 
{
	public:
		virtual const char* what() const throw();
};

class WrongDateFormatException : public std::exception 
{
	public:
		virtual const char* what() const throw();
};

class WrongFormatException : public std::exception 
{
	public:
		virtual const char* what() const throw();
};

class WrongValueFormatException : public std::exception 
{
	public:
		virtual const char* what() const throw();
};

#endif // !EXCEPTIONS_HPP