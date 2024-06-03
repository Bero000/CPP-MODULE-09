#include "RNP.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
        std::cerr << "Usage: " << av[0] << " [value]$" << std::endl;
    else
    {
        RPN values;
        values.initArgs(av[1]);
    }
}