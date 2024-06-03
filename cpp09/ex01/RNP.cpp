#include "RNP.hpp"

RPN::RPN()
{}
RPN::~RPN()
{}
RPN::RPN(const RPN& cpy)
{
    *this = cpy;
}
RPN& RPN::operator= (const RPN& value)
{
    if (this != &value)
        this->_rpn = value._rpn;
    return *this;
}

bool RPN::checkValue(const std::string arg)
{
    size_t numb = arg.find_first_not_of("\t\n\r 0123456789*/-+");
    size_t intCtrl = checkInt(arg);
    size_t operandCtrl = checkOperators(arg);
    if (arg.empty())
    {
        std::cerr << "Error: args can't be empty!"<< std::endl;
        return false;
    }
    if (numb != std::string::npos)
    {
        std::cerr << "Wrong value!"<< std::endl;
        return false;
    }
    if (intCtrl != operandCtrl + 1 || intCtrl == 0 || operandCtrl == 0)
    {
        std::cerr << "Wrong operands" << std::endl;
        return false;
    }
    return true;
}

int RPN::checkInt(const std::string i_int)
{
    size_t iValue = 0;

    for (size_t i = 0; i < i_int.size(); i++)
    {
        if (i_int[i] <= '9' && i_int[i] >= '0')
            iValue++;
    }

    return iValue;
}
int RPN::checkOperators(const std::string val)
{
    size_t opValue = 0;

    for (size_t i = 0; i < val.size(); i++)
    {
        if (val[i] == '-' || val[i] == '+' || val[i] == '*' || val[i] == '/')
            opValue++;
    }
    return opValue;
}

bool RPN::checkStream(const std::string val)
{
    std::istringstream value(val);
    if (value.fail() || !value.eof())
        return false;
    return true;
}

int RPN::hkTypeCast(const std::string& val)
{
    std::istringstream str(val);
    int i_int;

    str >> i_int;
    if (str.fail() || !str.eof())
    {
        std::cerr << "Error!"<< std::endl;
        return -1;
    }
    return i_int;
}

void RPN::initArgs(const std::string& arg)
{
    if (!checkValue(arg))
        return ;
    std::stack<int> myStack;
    std::istringstream strStream(arg);
    std::string operand;

    while (strStream >> operand)
    {
        if (operand == "+" || operand == "-" || operand == "*" || operand == "/")
        {
            if (myStack.size() < 2)
            {
                std::cerr << "Error: Invalid size!" << std::endl;
                return ;
            }
            int num2 = myStack.top();
            myStack.pop();
            int num1 = myStack.top();
            myStack.pop();
            int res = 0;

            if (operand == "+")
                res = num1 + num2;
            else if (operand == "-")
                res = num1 - num2;
            else if (operand == "*")
                res = num1 * num2;
            else if (operand == "/")
            {
                if (num2 == 0)
                {
                    std::cerr << "Error: divide error!"<< std::endl;
                    return ;
                }
                res = num1 / num2;
            }
            else
            {
                std::cerr << "Error: Invalid operator!" << std::endl;
            }
            myStack.push(res);
        }
        else
        {
            int ctrl = hkTypeCast(operand);
            if (ctrl == -1)
                return ;
            else
                myStack.push(ctrl);
        }
    }
    if (myStack.size() != 1)
    {
        std::cerr << "Error: Invalid expression format." << std::endl;
        return ;
    }
    std::cout << myStack.top() << std::endl;
}
