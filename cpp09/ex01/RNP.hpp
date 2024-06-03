#ifndef RNP_HPP
# define RNP_HPP

#include <iostream>
#include <algorithm>
#include <stack>
#include <deque>
#include <vector>
#include <sstream>


class RPN
{
    private:
        std::stack<int> _rpn;
    public:
        RPN();
        ~RPN();
        RPN(const RPN& cpy);
        RPN& operator= (const RPN& value);

        void initArgs(const std::string& arg);
        bool checkValue(const std::string arg);
        int checkInt(const std::string i_int);
        int checkOperators(const std::string val);
        bool checkStream(const std::string val);
        int hkTypeCast(const std::string& val);

};


#endif