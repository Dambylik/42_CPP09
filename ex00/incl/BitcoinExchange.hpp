/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:51:02 by okapshai          #+#    #+#             */
/*   Updated: 2025/03/23 16:51:15 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include "Colors.hpp"
#include "Exceptions.hpp"

# include <cstdlib>
# include <cstring>
# include <fstream>
# include <iostream>
# include <list>
# include <map>
# include <string>
# include <sstream>
# include <vector>
# include <utility>

 #include <cstdlib>

#define SUCCESS 0
#define ERROR 1

#define FALSE 0
#define TRUE 1

#define FEBRUARY 2
#define APRIL 4
#define JUNE 6
#define SEPTEMBER 9
#define NOVEMBER 11

#define DEBUG 0
// #define DEBUG 1


typedef std::map<std::string, double> map_t;

class BitcoinExchange
{
	private:

		map_t	_database;

	public:

		BitcoinExchange();
		~BitcoinExchange();

        BitcoinExchange(BitcoinExchange const & src);

		void	getInput(char *input);

		void	getDatabase(void);

		void	checkDate(std::string line);
		void	checkFormat(std::string line);
		void	checkValue(std::string line);
		void	printValue(std::string line);

		BitcoinExchange &	operator=(BitcoinExchange const & rhs);

};

std::ostream & operator<<(std::ostream & lhs, BitcoinExchange const & rhs);

#endif