#include "utils.h"
#include <iostream>
#include <limits>
#include <stdexcept>

double leerDouble(const std::string &mensaje)
{
    double valor;
    while (true)
    {
        std::cout << mensaje;
        std::cin >> valor;
        try
        {
            if (std::cin.fail() || valor < 0)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("Error: Debe ingresar un numero positivo.");
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return valor;
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << e.what() << std::endl;
        }
    }
}

int leerEntero(const std::string &mensaje)
{
    int valor;
    while (true)
    {
        std::cout << mensaje;
        std::cin >> valor;
        if (std::cin.fail())
        {
            std::cout << "Error: Debe ingresar un numero entero.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return valor;
        }
    }
}