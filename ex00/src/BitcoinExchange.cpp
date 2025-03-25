/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:52:29 by okapshai          #+#    #+#             */
/*   Updated: 2025/03/25 18:06:48 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
// ----------------------------------------------------------------------------
// ---------------------------------------------------------------- Constructor
// ----------------------------------------------------------------------------

BitcoinExchange::BitcoinExchange() : _database()
{
	if (DEBUG)
		std::cout << "BitcoinExchange base constructor called." << std::endl;
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const & src) : _database(src._database)
{
	if (DEBUG)
		std::cout << "BitcoinExchange copy constructor called." << std::endl;
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------- Destructor
// ----------------------------------------------------------------------------

BitcoinExchange::~BitcoinExchange()
{
	if (DEBUG)
		std::cout << "BitcoinExchange destructor called." << std::endl;
}

// ----------------------------------------------------------------------------
// ------------------------------------------------------------------- Overload
// ----------------------------------------------------------------------------

BitcoinExchange & BitcoinExchange::operator=(BitcoinExchange const & rhs)
{
	if (DEBUG)
		std::cout << "BitcoinExchange assignment operator called." << std::endl;

	this->_database = rhs._database;
	return *this;
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------- Exceptions
// ----------------------------------------------------------------------------

const char* ErrorException::what() const throw()
{
	return ("error.");
}

const char* FileOpeningException::what() const throw()
{
	return ("can't open file.");
}

const char* WrongDateFormatException::what() const throw()
{
	return ("format is Year-Month-Day.");
}

const char* WrongFormatException::what() const throw()
{
	return ("format is data | value.");
}

const char* WrongValueFormatException::what() const throw()
{
	return ("value must be either a float or a positive integer, between 0 and 1000.");
}

const char* ParseFailException::what() const throw()
{
	return ("Isstream failed to parse.\n");
}

// ----------------------------------------------------------------------------
// -------------------------------------------------------------------- Methods
// ----------------------------------------------------------------------------

void BitcoinExchange::getDatabase(void)
{
    // open the file
	std::ifstream infile("data.csv");
    
    // check if file was open successfully or if there is an error
	if (!infile.is_open() || infile.fail())
		throw(FileOpeningException());

    // reading the file
	std::string line;
	while (std::getline(infile, line))
	{
        // date = 10 first characters + extract date
		std::string date = line.substr(0, 10);

        // value starts on char 11 + extract value
		std::string valueStr = line.substr(11, (int)line.size());

        // parse && store value
		std::istringstream	iss(valueStr);
		char *valueNbr = new char[valueStr.length() + 1];
		std::strcpy(valueNbr, valueStr.c_str());

        // convert value to double
		if (iss >> valueNbr)
		{
			double valueDouble = atof(valueNbr);
			this->_database.insert(std::make_pair(date, valueDouble));
			delete[]valueNbr;
		}
		else
		{
			delete[] valueNbr;
			throw(ParseFailException());
		}
	}

    // close file
	infile.close();
}

void BitcoinExchange::checkDate(std::string line)
{
	bool isLeapYear = FALSE;

    // convert string to int
	int	Year = atoi(line.substr(0,4).c_str());

    // check if year is divisible by 4 || 400 but not 100
	if ((Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0))
		isLeapYear = TRUE;

    // extract month && day
	int	Month = atoi(line.substr(5,2).c_str());
	int	Day = atoi(line.substr(8,2).c_str());

    // Date validation
	if ((Month < 1 || Month > 12) || (Day < 1 || Day > 31))
		throw (WrongDateFormatException());

	if (Month == FEBRUARY && ((isLeapYear && Day > 29) || (!isLeapYear && Day > 28)))
		throw (WrongDateFormatException());

	if (Day > 30 && (Month == APRIL || Month == JUNE || Month == SEPTEMBER || Month == NOVEMBER))
		throw (WrongDateFormatException());
}


// make sure that data is at the right format
void BitcoinExchange::checkFormat(std::string line)
{
	std::string date = line.substr(0, 10);

	for (int i = 0; i < 13; i++)
	{
		if (i == 4 || i == 7)
		{
			if (line[i] != '-')
				throw(WrongDateFormatException());
		}

		else if (i == 10 || i == 12)
		{
			if (line[i] != ' ')
				throw(WrongFormatException());
		}

		else if (i == 11)
		{
			if (line[i] != '|')
				throw(WrongFormatException());
		}

		else
		{
			if (!isdigit(line[i]))
				throw(WrongDateFormatException());
		}
	}

	std::string value = line.substr(10);
}

// make sure that BitcoinExchange value format is right
void BitcoinExchange::checkValue(std::string line)
{
    // count positive signs
	int nbPositiveSign = 0;
	for (int i = 13; i < (int)line.size(); i++)
	{
		if (line[i] == '+')
			nbPositiveSign += 1;
		else
			break;
	}

    // extract the value, starts immediately after any + sign
	std::string value = line.substr(13 + nbPositiveSign, line.size());

    // check for dots and non digit characters
	int cptDot = 0;
	for (int i = 0; i < (int)value.size(); i++)
	{

        // count the number of '.'
		if (value[i] == '.')
		{
			cptDot += 1;
			if (cptDot > 1 || i > 4)
				throw(WrongValueFormatException());
		}

        // except for the decimal point, make sure that every character is a digit
		else if (!isdigit(value[i]))
			throw(WrongValueFormatException());
	}

    // make sure that a valid value is a four digit integer
    // or a decimal number with no more than four digits before the decimal point
	if (cptDot == 0 && value.size() > 4)
		throw(WrongValueFormatException());

    // extract data and check data
	std::istringstream iss(value);
    
    // store data into a dynamically allocated array
	char *valueNbr = new char[value.length() + 1];
	std::strcpy(valueNbr, value.c_str());

    // check if data is in range 0 - 1000
	if (iss >> valueNbr)
	{
		if (atoi(valueNbr) < 0 || atoi(valueNbr) > 1000)
		{
			delete[]valueNbr;
			throw(WrongValueFormatException());
		}
	}

	else
	{
		delete[] valueNbr;
		throw(ParseFailException());
	}

    // deallocate the allocated memory
	delete[] valueNbr;
}	


void BitcoinExchange::getInput(char *input)
{
    // open the input file
	std::ifstream infile(input);

    // check if file is open
	if (!infile.is_open() || infile.fail())
		throw(FileOpeningException());

    // read line from the file
	std::string line;
	while (std::getline(infile, line))
	{
		try {
			checkFormat(line);
			checkDate(line);
			checkValue(line);
			printValue(line);
		} catch(const std::exception& e) {
			std::cerr << "Error: " << e.what() << '\n';
		}
	}

    // close the file
	infile.close();
}

void BitcoinExchange::printValue(std::string line)
{
	std::string date = line.substr(0, 10);
	double amountBitcoin = atof(line.substr(13).c_str());
	map_t::const_iterator it = this->_database.find(date);
	map_t::const_iterator end = this->_database.end();
	if (it == end)
	{
		it = this->_database.upper_bound(date);
		if (it == this->_database.begin())
			throw(ErrorException());
		it--;
	}

	std::cout << date << " => " << amountBitcoin << " = " << (amountBitcoin * it->second) << "\n";
}