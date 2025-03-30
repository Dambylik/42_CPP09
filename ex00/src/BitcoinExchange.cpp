#include "BitcoinExchange.hpp"

// Canonical form implementations
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

    char* endptr;
    double value = strtod(str.c_str(), &endptr);
    
    if (*endptr != '\0') {
        throw std::runtime_error("Invalid number format");
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
    
    try {
        double val = stringToDouble(value);
        return val >= 0 && val <= 1000;
    } 
    catch (...) {
        return (false);
    }
}

void BitcoinExchange::loadDatabase() {

    const std::string filename = "data.csv";
    std::ifstream file(filename.c_str());
    if (!file.is_open() || file.peek() == std::ifstream::traits_type::eof()) {
        throw CsvFailToOpen();
    }

    std::string line;
    if (!std::getline(file, line) || line != "date,exchange_rate") {
        throw InvalidHeader();
    }

    int lineNumber = 1;
    while (std::getline(file, line)) {
        lineNumber++;
        std::istringstream ss(line);
        std::string date;
        std::string valueStr;
        if (!std::getline(ss, date, ',') || !std::getline(ss, valueStr)) {
            std::cerr << toString(lineNumber) << ": " << line << " ";
            throw DataError();
        }

        if (!isValidDate(date)) {
            std::cerr << toString(lineNumber) << ": " << date << " ";
            throw DateError();
        }
        
        double value;
        value = stringToDouble(valueStr);
        if (value < 0) {
            std::cerr << toString(lineNumber) << ": " << valueStr << " ";
            throw InvalidRate();
        }

        _csvDatabase[date] = value;
        if (_csvDatabase.empty()) {
            throw NoData();
        }
    }
}

std::string BitcoinExchange::toString( int number ) const {
    
    std::ostringstream ss;
    ss << number;
    return ss.str();
}

std::map<std::string, double>::const_iterator 
BitcoinExchange::findClosestDate( std::string const & date ) const {

    std::map<std::string, double>::const_iterator it = _csvDatabase.lower_bound(date);

    if (it == _csvDatabase.begin() || it->first == date) {
        //std::cout << "Date found: " << it->first << ", Exchange rate: " << it->second << std::endl;
        return it;
    }
    if (it == _csvDatabase.begin()) {
        throw std::runtime_error("No earlier date available");
    }
    --it;
    //std::cout << "Closest date: " << it->first << ", Exchange rate: " << it->second << std::endl;
    return it;
}

void BitcoinExchange::processLine( std::string const & line ) {

    if (line.empty())
        return;
    if (line.find(',') != std::string::npos) {
        return;
    }
    size_t delimPos = line.find(" | ");
    if (delimPos == std::string::npos) {
        throw std::runtime_error("Bad input => " + line);
    }
    std::string date = trim(line.substr(0, delimPos));
    std::string valueStr = trim(line.substr(delimPos + 3));

    if (!isValidDate(date)) {
        throw std::runtime_error("Invalid date => " + date);
    }

    if (!isValidValue(valueStr)) {
        throw std::runtime_error("Invalid value => " + valueStr);
    }

    double value = stringToDouble(valueStr);
    std::map<std::string, double>::const_iterator rateIt = findClosestDate(date);

    if (rateIt == _csvDatabase.end()) {
        throw std::runtime_error("No exchange rate found for date");
    }
    double result = value * rateIt->second;
    std::cout << date << " => " << value << " = " << result << std::endl;
}

void BitcoinExchange::processInputFile( std::string const & filename ) {

    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        throw std::runtime_error("Could not open input file");
    }

    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        try {
            line = trim(line);
            if (line.empty())
                continue;
            processLine(line);
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}
