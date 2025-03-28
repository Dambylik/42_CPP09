/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:52:29 by okapshai          #+#    #+#             */
/*   Updated: 2025/03/28 12:43:08 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

Bitcoin::Bitcoin() {
	std::ifstream csvFile("./src/data.csv");
	std::string line;

	setMonths(); // // Initialize months with days
	if (csvFile.is_open()) {
		std::getline(csvFile, line);  // Read header
		if (csvFile.peek() == std::ifstream::traits_type::eof()) // checks if it’s empty 
			throw CsvFail();
		if (line.compare("date,exchange_rate") != 0)
			throw InvalidHeader(); // or has a valid header
		while (std::getline(csvFile, line))
			csvDataBase.insert(std::make_pair(saveDate(line), saveRate(line))); // Loads exchange rates into a std::map, where: Key = Date (YYYY-MM-DD) Value = Exchange rate (float)
		csvFile.close();
		validDataBase(); //to ensure all data is valid.
	}
	else
		throw NoData();
	return;
}

Bitcoin::Bitcoin( Bitcoin const & other ) { *this = other; }

Bitcoin & Bitcoin::operator=( Bitcoin const & other ) {
	this->months = other.months;
	this->csvDataBase = other.csvDataBase;
	return (*this);
}

Bitcoin::~Bitcoin() {}

//-------------------------------------------------------------------Methods

void Bitcoin::validDataBase() {
	std::map<std::string, float>::iterator dataIt = csvDataBase.begin();
	for (; dataIt != csvDataBase.end(); dataIt++) {
		if (validDate(dataIt->first) == false)
            throw CsvFail();
		if (dataIt->second < 0)
            throw CsvFail();
	}
}

void Bitcoin::isInputCorrect( char **argv ) {
    std::string inputFile = argv[1];

    // Check if the file ends with ".csv" or ".txt"
    if (inputFile.size() <= 4 || 
        (inputFile.rfind(".csv") != inputFile.size() - 4 && 
         inputFile.rfind(".txt") != inputFile.size() - 4)) {
        throw WrongExtension();
    }

    chechkInputFile(inputFile);
}

//Ensures the file is readable
// Checks if the first line is a valid header (date,exchange_rate for .csv or date | value for .txt).
void Bitcoin::chechkInputFile(std::string inputFile) {
    
    std::ifstream input(("./" + inputFile).c_str());
    std::string line;

    if (!input.is_open()) {
        throw CsvFail();
    }
    std::getline(input, line); // Read first line
    if (inputFile.rfind(".csv") != std::string::npos) {
        if (line.compare("date,exchange_rate") != 0) {
            throw InvalidHeader();
        }
    } else if (inputFile.rfind(".txt") != std::string::npos) {
        if (line.compare("date | value") != 0) {
            throw InvalidHeader();
        }
    }
    input.close();
}

// Reads each line, extracts date and value.
// Validates the data (validData()).
// Fetches the exchange rate for the date (getExchangeRate()).
// Calculates and prints the exchanged value.
//2023-03-15 | 2.5 to 2023-03-15 => 2.5 = 137.50

void Bitcoin::exchange(std::string inputFile) {
    
    std::ifstream input(("./" + inputFile).c_str());
    std::string line;

    if (!input.is_open()) {
        throw NoData();
    }

    int i = 0;
    while (std::getline(input, line)) {
        if (i++ == 0) continue; // Skip header

        std::string date, value;
        size_t separatorPos = line.find(" | ");
        if (separatorPos == std::string::npos) {
            separatorPos = line.find(","); // Allow "date,value"
        }
        if (separatorPos == std::string::npos) {
            std::cout << FRED("Error: bad input => ") << line << std::endl;
            continue;
        }

        date = line.substr(0, separatorPos);
        value = line.substr(separatorPos + 3); // Ignore "| " (or ", ")

        if (validData(line)) {
            float coins = std::atof(value.c_str());
            float exchangeRate = getExchangeRate(date);

            if (exchangeRate != -42) {
                std::cout << date << " => " << coins << " = "<< std::setprecision(2)
                          		<< coins * exchangeRate << std::endl;
            }
        }
    }

    input.close();
}

// Extracts date and value.
// Validates the date (validDate()) and value (validValue()).
bool Bitcoin::validData(std::string line) {
    size_t pos = line.find(" | ");
    if (pos == std::string::npos) {
        std::cout << FRED("Error: bad input => ") << line << std::endl;
        return false;
    }

    std::string date = line.substr(0, pos);
    std::string value = line.substr(pos + 3);

    return validDate(date) && validValue(value);
}


std::string Bitcoin::saveDate(std::string line) const { return line.substr(0, line.find(",")); }

float Bitcoin::saveRate(std::string line) const {
	if (line.find(",") != std::string::npos && line[line.size() - 1] != ',')
		return std::atof(line.substr(line.find(",") + 1).c_str());
	else
		throw CsvFail();
	return -42;
}

bool Bitcoin::validDate(std::string line) {
    
	std::string date = line.substr(0, line.find(" "));
	std::string year = date.substr(0, date.find("-"));
	std::string month = date.substr(5, 2);
	std::string day = date.substr(8, 2);
	std::stringstream yy(year), mm(month), dd(day);
	int int_Y;
    int int_M;
    int int_D;
	yy >> int_Y, mm >> int_M, dd >> int_D;

	if (int_Y < 1970 || int_Y > 2042) {
        std::cout << "Error: The year is invalid." << std::endl;
        return  (false);
    }
        
	if (validMonth(month) == false) {
        std::cout << "Error: The month is invalid." << std::endl;
        return (false);
    }
    
	if (validDay(day, month) == false) {
        std::cout << "Error: The day is invalid." << std::endl;
        return (false);
    }
     
	return (true);
}

bool Bitcoin::validMonth(std::string month) {
	std::map<int, int>::iterator monthIt = months.begin();
	if (month[0] == '0' && month.length() == 2) month = month.substr(1);
	for (; monthIt != months.end(); monthIt++)
		if (monthIt->first == std::atoi(month.c_str()))
        return true;
	return false;
}

bool Bitcoin::validDay(std::string day, std::string month) {
    int d = std::atoi(day.c_str());
    int m = std::atoi(month.c_str());

    if (m < 1 || m > 12) return false;

    if (m == 2) { // February check
        return (d >= 1 && d <= 29);
    }
    
    if (m == 4 || m == 6 || m == 9 || m == 11) { // Months with 30 days
        return (d >= 1 && d <= 30);
    }

    return (d >= 1 && d <= 31); // Other months
}

bool Bitcoin::validValue(std::string line) {
    float num = std::atof(line.c_str());
    if (num < 0) {
        std::cout << FRED("Error: not a positive number.") << std::endl;
        return (false);
    }
    if (num > 1000) {
        std::cout << FRED("Error: too large a number.") << std::endl;
        return (false);
    }
    return (true);
}

// Finds the closest exchange rate for the given date.
// If there’s no exact match, it picks the nearest earlier date.

float Bitcoin::getExchangeRate(std::string date) {
    std::map<std::string, float>::iterator it = csvDataBase.lower_bound(date);

    if (it == csvDataBase.begin()) {
        std::cout << "Error: csv database has no information about this date." << std::endl;
        return (-42);
    }

    if (it == csvDataBase.end() || it->first != date) {
        --it; // Get the closest lower date
    }

    return it->second;
}

void Bitcoin::setMonths() {
    
	months.insert(std::make_pair(1, 31));
	months.insert(std::make_pair(2, 28));
	months.insert(std::make_pair(3, 31));
	months.insert(std::make_pair(4, 30));
	months.insert(std::make_pair(5, 31));
	months.insert(std::make_pair(6, 30));
	months.insert(std::make_pair(7, 31));
	months.insert(std::make_pair(8, 31));
	months.insert(std::make_pair(9, 30));
	months.insert(std::make_pair(10, 31));
	months.insert(std::make_pair(11, 30));
	months.insert(std::make_pair(12, 31));
}