/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 19:09:31 by okapshai          #+#    #+#             */
/*   Updated: 2025/03/31 15:09:24 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main( int argc, char **argv ) {
    
	if (argc != 2) {
        std::cerr << BOLD(FRED("Error: could not open file.")) << std::endl;
        return (1);
    }

    BitcoinExchange coin;

    try {
        coin.loadDatabase();
        coin.processInputFile(argv[1]);
    } 
    catch (const std::exception & e) {
        std::cerr << BOLDRED << e.what() << RESET << std::endl;
        return (1);
    }
    return (0);
}