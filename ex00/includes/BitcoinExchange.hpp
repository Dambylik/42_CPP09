/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:51:02 by okapshai          #+#    #+#             */
/*   Updated: 2025/03/26 18:32:03 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Colors.hpp"
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#define INVALID "Error: bad input => "
#define WRONGDAY "Error: The day is invalid."
#define WRONGYEAR "Error: The year is invalid."
#define WRONGMONTH "Error: The month is invalid."
#define CSVFAIL "Error: csv database is corrupted."
#define WRONGEXT "This program only runs with a .csv or .txt file."
#define WRONGARG "This program only runs with 2 arguments."
#define NODATA "We have backup right? Yes. Where? On the server..."
#define TOOBIG "Error: too large a number."
#define NOTPOS "Error: not a positive number."
#define NODATAONDATE "Error: csv database has no information about this date."

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
