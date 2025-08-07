#include <iostream>
#include <iomanip>
#include "utils.h"
#include "problema.h"
#include "simplex.h"
#include "grafico.h"

void mostrarMenu()
{
    std::cout << "\n.----------------------------------------------------.\n";
    std::cout << "|   Sistema de Optimizacion Flair Furniture Company  |\n";
    std::cout << "'----------------------------------------------------'\n";
    std::cout << "1. Ingresar precios de venta\n";
    std::cout << "2. Ingresar restricciones de produccion\n";
    std::cout << "3. Definir funcion de ganancia\n";
    std::cout << "4. Calcular solucion optima\n";
    std::cout << "5. Mostrar solucion grafica\n";
    std::cout << "6. Salir\n";
    std::cout << "------------------------------------------------------\n";
}

int main()
{
    std::cout << std::fixed << std::setprecision(2);
    DatosProblema datos;
    SolucionOptima solucion;
    bool preciosIngresados = false;
    bool restriccionesIngresadas = false;

    int opcion;
    do
    {
        mostrarMenu();
        opcion = leerEntero("Seleccione una opcion: ");

        switch (opcion)
        {
        case 1:
            ingresarPrecios(datos);
            preciosIngresados = true;
            break;
        case 2:
            ingresarRestricciones(datos);
            restriccionesIngresadas = true;
            break;
        case 3:
            definirFuncionObjetivo(datos, preciosIngresados);
            break;
        case 4:
            calcularSolucionOptima(datos, solucion, preciosIngresados, restriccionesIngresadas);
            break;
        case 5:
            mostrarGrafico(datos, solucion);
            break;
        case 6:
            std::cout << "\nGracias por usar el sistema de optimizacion, vuelva pronto.\n"
                      << std::endl;
            break;
        default:
            std::cout << "\n>> Opcion no valida. Por favor, intente de nuevo.\n";
            break;
        }
    } while (opcion != 6);

    return 0;
}