/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 19:09:31 by okapshai          #+#    #+#             */
/*   Updated: 2025/03/30 20:16:36 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main( int argc, char **argv ) {
    
	if (argc != 2) {
        std::cerr << FRED("Usage: ") << FRED(argv[0]) << FRED(" <input file>") << std::endl;
        return (1);
    }

    BitcoinExchange coin;

    try {
        coin.loadDatabase();
        coin.processInputFile(argv[1]);
    } 
    catch (const std::exception & e) {
        std::cerr <<  FRED(e.what()) << std::endl;
        return (1);
    }
    return (0);
}