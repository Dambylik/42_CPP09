/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:51:34 by okapshai          #+#    #+#             */
/*   Updated: 2025/04/14 12:33:25 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <exception>

class ErrorTimeException : public std::exception 
{
	public:
		virtual const char* what() const throw() {
			return ("Error: an error occured using gettimeoftheday()");
		}
};

class WrongInputException : public std::exception 
{
	public:
		virtual const char* what() const throw() {
			return ("Error: please enter unsigned ints only");
		}
};
