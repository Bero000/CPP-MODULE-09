#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
    dataFileOpen();
}
BitcoinExchange::~BitcoinExchange()
{}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& cpy)
{
    *this = cpy;
}
BitcoinExchange& BitcoinExchange::operator= (const BitcoinExchange& value)
{
    if (this != &value)
    {
        this->_map = value._map;
    }
    return *this;
}

void BitcoinExchange::openFileControl(const std::string av)
{   
    std::ifstream input(av);
    if (!input.is_open())
    {
        std::cerr << "Can't open!"<< std::endl;
        return ;
    }
    std::string header;
    std::getline(input, header);
    if (!headerControl(header))
    {
        std::cerr << "date | value error!"<< std::endl;
        return ;
    }
    std::string readingLine;
    while (std::getline(input, readingLine))
    {
        std::string::size_type pos = readingLine.find(" | ");
        std::string::size_type position = readingLine.find_first_not_of("\n\t ");
        if (pos == std::string::npos)
        {
            std::cerr << "Error: bad input => " << readingLine << std::endl;
            continue;
        }
        const std::string date = readingLine.substr(0, pos);
        std::string value = readingLine.substr(pos + 3);
        if (!checkDateInRange(date) || position == std::string::npos)
            continue;
        if (!doubleControl(value))
            continue;
        double doubleValue = atof(value.c_str());
        if (!validateInputDate(value) || !validDateControl(date))
        {
            std::cerr << "Error: bad input => " << date << std::endl;
            continue;
        }
        std::map<std::string, double>::iterator it = _map.lower_bound(date);
        if (it == _map.end() || it->first != date) 
        {
            if (it != _map.begin())
                --it;
            else
            {
                std::cerr << "Error: bad input => " << date << std::endl;
                continue;
            }
        }
        std::cout << date << " => " << value << " = " << it->second * doubleValue << std::endl;
    }
    input.close();
}

bool BitcoinExchange::validDateControl(const std::string& date)
{
    if (date[4] != '-' || date[7] != '-' || date.size() != 10)
        return false;
    if (date.find_first_not_of("-0123456789") != std::string::npos)
        return false;
    for (unsigned int i = 0; i < date.size(); i++)
    {
        if (date[i] == '-' || date[i] == ',')
            continue;
        if (!std::isdigit(date[i]))
            return false;
    }
    return true;
}

bool BitcoinExchange::isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
bool BitcoinExchange::isDateValid(int year, int month, int day)
{
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month < 1 || month > 12 || day < 1 || day > 31) 
        return false;
    if (isLeapYear(year))
        daysInMonth[1] = 29;
    return day <= daysInMonth[month - 1];
}
bool BitcoinExchange::checkDateInRange(const std::string& date)
{
    std::istringstream iss(date);
    int year, month, day;
    char ch1, ch2;
    iss >> year >> ch1 >> month >> ch2 >> day;

    if (year < 2009 || (year == 2009 && (month < 1 || (month == 1 && day < 2)))) 
    {
        std::cerr << "Error: Date is before 2009-01-02: " << date << std::endl;
        return false;
    }
    if (year > 2022 || (year == 2022 && (month > 3 || (month == 3 && day > 29)))) 
    {
        std::cerr << "Error: Date is after 2022-03-29: " << date << std::endl;
        return false;
    }
    if (!isDateValid(year, month, day))
    {
        std::cerr << "Error: bad input => " << date << std::endl;
        return false;
    }
    return true;
}
bool BitcoinExchange::validateInputDate(const std::string& value)
{
    std::istringstream isString(value);
    double val;
    isString >> val;

    if (isString.fail() || !isString.eof())
        return false;
    return true;
}

bool BitcoinExchange::doubleControl(const std::string& value)
{
    double d_value = atof(value.c_str());
    if (d_value < 0)
    {
        std::cerr << "Error: not a positive number." << std::endl;
        return false;
    }
    if (d_value > 1000)
    {
        std::cerr << "Error: too large a number." << std::endl;
        return false;       
    }
    return true;
}

void	BitcoinExchange::BitcoinExchange::dataFileOpen(void)
{
	std::ifstream	dFile("data.csv");
	std::string		line;
	std::string		key;
	std::string		value;
	std::string::size_type	pos;

	if (!dFile.is_open())
		throw std::runtime_error("Data file not found!");
	std::getline(dFile, line);
    if (line.empty())
        throw std::runtime_error("Data file can't be empty!");
	while (std::getline(dFile, line))
	{
		pos = line.find(",");
		if (pos == std::string::npos)
			continue;
		key = line.substr(0, pos);
		value = line.substr(pos + 1);
		_map[key] = atof(value.c_str());
	}
	dFile.close();
}

bool BitcoinExchange::headerControl(const std::string header)
{
    if (header != "date | value")
        return false;
    return true;
}
