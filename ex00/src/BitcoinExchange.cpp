/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:18:04 by okapshai          #+#    #+#             */
/*   Updated: 2025/04/14 11:49:30 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange( BitcoinExchange const & other ) : _csvDatabase(other._csvDatabase) {}

BitcoinExchange& BitcoinExchange::operator=( BitcoinExchange const & other ) {
    if (this != &other) {
        _csvDatabase = other._csvDatabase;
    }
    return (*this);
}

BitcoinExchange::~BitcoinExchange() {}


//-------------------------------------------------------------------Methods

void BitcoinExchange::loadDatabase() {

    const std::string filename = "data.csv";
    std::ifstream file(filename.c_str());
    if (!file.is_open() || file.peek() == std::ifstream::traits_type::eof()) {
        throw CsvFailToOpen();
    }

    std::string line;
    if (!std::getline(file, line)) {
        throw InvalidHeader();
    }

    int lineNumber = 1;
    while (std::getline(file, line))
    {
        lineNumber++;
        std::istringstream ss(line);
        std::string date;
        std::string valueStr;

        if (!std::getline(ss, date, ',') || !std::getline(ss, valueStr)) {
            std::cerr << BOLDRED << "Error: Invalid database format. => " << toString(lineNumber) << ": " << line << RESET << std::endl;
            throw DataError();
        }

        if (!isValidDate(date)) {
            std::cerr << BOLDRED << "Error: Invalid date in database. => " << toString(lineNumber) << ": " << date << RESET << std::endl;
            throw DataError();
        }
        
        double value;
        value = stringToDouble(valueStr);
        if (value < 0) {
            std::cerr << BOLDRED << "Error: Invalid exchange rate. => " << toString(lineNumber) << ": " << valueStr << RESET << std::endl;
            throw DataError();
        }

        _csvDatabase[date] = value;
        if (_csvDatabase.empty()) {
            throw NoData();
        }
    }
}

void BitcoinExchange::processInputFile( std::string const & filename ) {

    std::ifstream file(filename.c_str());
    if (!file.is_open() || file.peek() == std::ifstream::traits_type::eof()) {
        throw InputFailToOpen();
    }

    std::string line;
    if (!std::getline(file, line)) {
        throw NoData();
    }

    int lineNumber = 1;
    while (std::getline(file, line)) {
        lineNumber++;
       try {
            line = trim(line);
            if (line.empty())
                continue;
            processLine(line);
        }
        catch (const std::exception & e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

void BitcoinExchange::processLine(std::string const & line) {
    
    if (line.find(',') != std::string::npos) {
        std::cerr << BOLDRED << "Error: Invalid database format. => " << RESET << line << std::endl;
        return;
    }

    size_t delimPos = line.find(" | ");
    if (delimPos == std::string::npos) {
        std::cerr << BOLDRED << "Error: bad input => " << line << RESET << std::endl;
        return;
    }

    std::string date = trim(line.substr(0, delimPos));
    std::string valueStr = trim(line.substr(delimPos + 3));

    if (!isValidDate(date)) {
        std::cerr << BOLDRED << "Error: Invalid date => " << date << RESET << std::endl;
        return;
    }

    if (!isValidValue(valueStr)) {
        return;
    }

    double value = stringToDouble(valueStr);
    std::map<std::string, double>::const_iterator rateIt = findClosestDate(date);

    if (rateIt == _csvDatabase.end()) {
        std::cerr << BOLDRED << "Error: No exchange rate found for date" << RESET << std::endl;
        return;
    }

    double result = value * rateIt->second;
    std::cout << date << " => " << value << " = " << result << std::endl;
}

std::string BitcoinExchange::toString( int number ) const {
    
    std::ostringstream ss;
    ss << number;
    return ss.str();
}


std::map<std::string, double>::const_iterator BitcoinExchange::findClosestDate( std::string const & date ) const {

    std::map<std::string, double>::const_iterator it = _csvDatabase.lower_bound(date);

    if (it == _csvDatabase.begin() || it->first == date) {
        // std::cout << GREEN << "Date found: " << RESET << it->first 
        //             << GREEN  << ", Exchange rate: " << RESET << it->second << std::endl;
        return (it);
    }
    if (it == _csvDatabase.begin()) {
        throw std::runtime_error("No earlier date available");
    }
    --it;
    // std::cout << YELLOW << "Closest date: " << RESET << it->first 
    //             << YELLOW  << ", Exchange rate: " << RESET << it->second << std::endl;
    return (it);
}

std::string BitcoinExchange::trim( const std::string & str ) const {

    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");
    if (first == std::string::npos) {
        return ("");
    }
    else {
        return (str.substr(first, (last - first + 1)));
    }
}

double BitcoinExchange::stringToDouble( std::string const & str ) const {

    if (str.find_first_not_of("0123456789.-") != std::string::npos) {
        return (-2);
    }
    char* endptr;
    double value = strtod(str.c_str(), &endptr);
    
    if (*endptr != '\0') {
        std::cerr << BOLDRED << "Error: Failed to convert string to double => " << str << RESET << std::endl;
        return (-1);
    }
    return (value);
}

bool BitcoinExchange::isValidDate( std::string const & date ) const {

    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return (false);

    int year = atoi(date.substr(0, 4).c_str());
    int month = atoi(date.substr(5, 2).c_str());
    int day = atoi(date.substr(8, 2).c_str());

    if (year <= 1950 || year >= 2050 || month < 1 || month > 12 || day < 1 || day > 31)
        return (false);

    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
        daysInMonth[1] = 29;

    if (day > daysInMonth[month - 1]) {
        return (false);
    }
    return (true);
}

bool BitcoinExchange::isValidValue( std::string const & value ) const {

    double val = stringToDouble(value);
    
    if (val < 0) {
        std::cerr << BOLDRED << "Error: not a positive number." << RESET << std::endl;
        return (false);
    }
    else if (val > 1000) {
        std::cerr << BOLDRED << "Error: too large a number." << RESET << std::endl;
        return (false);
    }
    return (true);
}
