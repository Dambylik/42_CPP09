/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:52:59 by okapshai          #+#    #+#             */
/*   Updated: 2025/04/02 18:37:05 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Rpn.hpp"

int	main(int argc, char **argv) {
	
	if (argc != 2) {
		std::cerr << FRED("Error: Usage is ./RPN <RPN expression>\n"); 
		return (1);
	}

	RPN rpn;
	
	try {
		rpn.processInput(argv[1]); // Ensures the input contains only digits, spaces, and operators. 
		rpn.calculateRpn(argv[1]); // Reads the input and performs calculations using a stack.

		std::cout << FGRN(rpn.getResult()) << std::endl; // Print the final result
		return (0);
	}
	catch( const std::exception & e ) {
		std::cerr << FRED("Error: ") << FRED(e.what()) << '\n';
	}
	return (1);
}

