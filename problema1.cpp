#include "problema.h"
#include "utils.h"
#include <iostream>
#include <iomanip>

void ingresarPrecios(DatosProblema &datos)
{
    std::cout << "\n--- Ingreso de Precios/Beneficios ---\n";
    datos.precio_x1 = leerDouble("Ingrese el beneficio de cada mesa (p1): ");
    datos.precio_x2 = leerDouble("Ingrese el beneficio de cada silla (p2): ");
    std::cout << "Beneficios registrados: mesas $" << datos.precio_x1 << " y sillas $" << datos.precio_x2 << std::endl;
}

void ingresarRestricciones(DatosProblema &datos)
{
    std::cout << "\n--- Ingreso de Restricciones de Produccion ---\n";
    std::cout << "Se usarán las restricciones del problema de Flair Furniture:\n";

    datos.restricciones.clear();
    datos.restricciones.push_back({4.0, 3.0, 240.0}); // Carpintería
    datos.restricciones.push_back({2.0, 1.0, 100.0}); // Pintura
    datos.restricciones.push_back({0.0, 1.0, 60.0});  // Límite de sillas

    std::cout << "Restricciones registradas:\n";
    std::cout << "  - Carpinteria: 4x1 + 3x2 <= 240\n";
    std::cout << "  - Pintura: 2x1 + x2 <= 100\n";
    std::cout << "  - Produccion Sillas: x2 <= 60\n";
}

void definirFuncionObjetivo(const DatosProblema &datos, bool preciosIngresados)
{
    if (!preciosIngresados)
    {
        std::cout << ">> Usando beneficios por defecto. Para cambiarlos, use la opcion 1.\n";
    }
    std::cout << "\n--- Funcion de Ganancia ---\n";
    std::cout << "Funcion a maximizar: Z = " << datos.precio_x1 << "x1 + " << datos.precio_x2 << "x2" << std::endl;
}