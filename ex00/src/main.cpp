/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:52:59 by okapshai          #+#    #+#             */
/*   Updated: 2025/03/27 17:44:54 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv) {
	try {
		if (argc != 2)
			throw WrongArg();
		Bitcoin coin;
		coin.isInputCorrect(argv); // Ensures the file has the correct extension (.csv or .txt).
		coin.exchange(argv[1]);
	}
	catch (const std::exception& e) {
		std::cout << FRED(e.what()) << std::endl;
	}
	return (0);
}

void Bitcoin::printMap(const std::map<std::string, float>& dataBaseType) {
    int i = 0;
    for (std::map<std::string, float>::const_iterator it = dataBaseType.begin();
         it != dataBaseType.end(); ++it) {
        std::cout << i++ << ": " << it->first << " | " << it->second << std::endl;
    }
}
