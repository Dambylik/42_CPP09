/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:51:02 by okapshai          #+#    #+#             */
/*   Updated: 2025/03/30 20:10:51 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
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

#define FALSE 0
#define TRUE 1

#define FEBRUARY 2
#define APRIL 4
#define JUNE 6
#define SEPTEMBER 9
#define NOVEMBER 11


class BitcoinExchange {	

	public:
	
		BitcoinExchange();
		BitcoinExchange( BitcoinExchange const & other ) ;
		BitcoinExchange& operator=( BitcoinExchange const & other );
		~BitcoinExchange();
		
		void 							loadDatabase();
		void 							processInputFile( std::string const & filename );

		bool 							isValidDate( std::string const & date ) 		const;
		bool 							isValidValue( std::string const & value ) 		const;
		std::string 					trim( std::string const & str ) 				const;
		double 							stringToDouble( std::string const & str ) 		const;
		void 							processLine( std::string const & line );
		std::string 					toString( int number ) const;
		
		std::map<std::string, double>::const_iterator findClosestDate(const std::string& date) const;

	private:
	
		std::map<std::string, double> 	_csvDatabase;
};
std::ostream & operator<<(std::ostream & lhs, BitcoinExchange const & rhs);