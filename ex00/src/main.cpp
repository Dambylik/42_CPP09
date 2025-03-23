/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:52:59 by okapshai          #+#    #+#             */
/*   Updated: 2025/03/23 16:54:00 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int ac , char **av){

    if (ac != 2) {
		std::cerr << "Error: Usage is ./btc <file>.\n";
		return (ERROR);
	}

	BitcoinExchange btc;

	try {
		btc.getDatabase();
		btc.getInput(av[1]);
		return (SUCCESS);
	} catch(const std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
	}

	return (ERROR);
}