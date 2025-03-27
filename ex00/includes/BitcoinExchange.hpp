/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:51:02 by okapshai          #+#    #+#             */
/*   Updated: 2025/03/27 17:41:38 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Colors.hpp"
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include "Exceptions.hpp"  


class Bitcoin {
	
	public:
		Bitcoin();
		~Bitcoin();
		Bitcoin( Bitcoin const & other );
		Bitcoin & operator=( Bitcoin const & other );

		void 							setMonths();
		// CSV FILE
		float 							saveRate( std::string line ) const;
		std::string 					saveDate( std::string line ) const;
		void 							validDataBase();
		// INPUT FILE
		void 							isInputCorrect( char **argv );
		void 							chechkInputFile( std::string inputFile );
		std::map<std::string, float> 	getCsvData() const;
		// EXCHANGE AND VALUE CHECKS
		bool 							validDate( std::string line );
		bool 							validData( std::string line );
		bool 							validValue( std::string line );
		bool 							validMonth( std::string month );
		void 							exchange( std::string inputFile );
		float 							getExchangeRate( std::string date );
		bool 							validDay( std::string day, std::string month );

		// for testing
		void 							printMap(const std::map<std::string, float>& dataBaseType);

	private:
		std::map<std::string, float> 	csvDataBase;  // data and exchange rate
		std::map<int, int> 				months;		// months with days
};
