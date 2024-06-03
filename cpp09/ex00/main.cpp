#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Usage: " << av[0] << " <filename>" << std::endl;
        return 1;
    }
    else
    {
        try
        {
            BitcoinExchange btc;
            btc.openFileControl(av[1]);
        }
        catch(std::runtime_error& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
}