#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <algorithm>
#include <stack>
#include <map>
#include <deque>
#include <vector>
#include <fstream>
#include <sstream>
#include <cctype>

class BitcoinExchange
{
    private:
        std::map<std::string, double> _map;
    public:
        BitcoinExchange();
        ~BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& cpy);
        BitcoinExchange& operator= (const BitcoinExchange& value);
        
        void openFileControl(const std::string av);
        bool validDateControl(const std::string& date);
        bool doubleControl(const std::string& value);

        bool isLeapYear(int year);
        bool isDateValid(int year, int month, int day);
        bool checkDateInRange(const std::string& date);
        bool validateInputDate(const std::string &value);
        void dataFileOpen(void);
        bool headerControl(const std::string header);
};


#endif