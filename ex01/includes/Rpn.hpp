/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rpn.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:51:02 by okapshai          #+#    #+#             */
/*   Updated: 2025/04/02 18:30:59 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Colors.hpp"
#include "Exceptions.hpp"
#include <iostream>
#include <string>
#include <stack>

// RPN is a mathematical notation where operators follow their operands. Instead of writing:
// Infix Notation (standard math):3 + 4
// RPN Notation:3 4 +
// The main advantage of RPN is that it does not require parentheses. 
// The order of operations is determined only by the position of the operands and operators.

class RPN
{
	public:

		RPN();
		RPN( RPN const & other) ;
		RPN & operator=(RPN const & other);
		
		~RPN();

		int const & getResult(void) const;

		void 			performCalculation( char oper, int firstNB, int secondNb );
		bool 			isOperator( char c );
		void 			processInput( std::string input );
		void 			calculateRpn( std::string input );

	private:

		int				_result;
		std::stack<int> _stack;
};