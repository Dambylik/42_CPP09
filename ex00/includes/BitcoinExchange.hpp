/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:51:02 by okapshai          #+#    #+#             */
/*   Updated: 2025/04/14 11:38:30 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Colors.hpp"
#include "Exceptions.hpp"
# include <fstream>
# include <map>
#include <cstdlib>
#include <iomanip>


class BitcoinExchange {	

	public:
	
		BitcoinExchange();
		BitcoinExchange( BitcoinExchange const & other ) ;
		BitcoinExchange & operator=( BitcoinExchange const & other );
		~BitcoinExchange();
		
		void 							loadDatabase();
		void 							processInputFile( std::string const & filename );
		void 							processLine(std::string const & line);
		bool 							isValidDate( std::string const & date ) 		const;
		bool 							isValidValue( std::string const & value ) 		const;
		std::string 					trim( std::string const & str ) 				const;
		double 							stringToDouble( std::string const & str ) 		const;
		std::string 					toString( int number ) 							const;
		
		std::map<std::string, double>::const_iterator findClosestDate(const std::string & date) const;

	private:
	
		std::map<std::string, double> 	_csvDatabase;
};
