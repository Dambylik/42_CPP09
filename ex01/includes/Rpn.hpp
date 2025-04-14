/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rpn.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:51:02 by okapshai          #+#    #+#             */
/*   Updated: 2025/04/14 11:57:11 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Colors.hpp"
#include "Exceptions.hpp"
#include <iostream>
#include <string>
#include <stack>

class RPN {
	
	public:

		RPN();
		RPN( RPN const & other) ;
		RPN & operator=( RPN const & other );
		~RPN();

		int const & 	getResult( void ) const;

		void 			performCalculation( char oper, int firstNB, int secondNb );
		bool 			isOperator( char c );
		void 			processInput( std::string input );
		void 			calculateRpn( std::string input );

	private:

		int				_result;
		std::stack<int> _stack;
};