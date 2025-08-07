#include "simplex.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <limits>

const double EPSILON = 1e-9; // Para manejar la precision de los numeros de punto flotante

void calcularSolucionOptima(const DatosProblema &datos, SolucionOptima &sol, bool precios, bool restricciones)
{
    if (!restricciones)
    {
        std::cout << "\n>> Error: Primero debe definir las restricciones en la opcion 2.\n";
        return;
    }
    if (!precios)
    {
        std::cout << "\n>> Error: Primero debe ingresar los precios en la opcion 1.\n";
        return;
    }

    std::cout << "\n--- Calculando la Solucion Optima (Algoritmo Simplex)... ---\n";

    // 1. Preparar la tabla Simplex inicial
    const int num_vars = 2;
    const int num_rest = datos.restricciones.size();
    const int num_cols = num_vars + num_rest + 1;
    const int num_rows = num_rest + 1;

    std::vector<std::vector<double>> tabla(num_rows, std::vector<double>(num_cols, 0.0));

    // Llenar la fila de la funcion objetivo Z
    tabla[0][0] = -datos.precio_x1;
    tabla[0][1] = -datos.precio_x2;

    // Llenar las filas de las restricciones
    for (int i = 0; i < num_rest; ++i)
    {
        tabla[i + 1][0] = datos.restricciones[i].coef_x1;
        tabla[i + 1][1] = datos.restricciones[i].coef_x2;
        tabla[i + 1][i + num_vars] = 1.0;
        tabla[i + 1][num_cols - 1] = datos.restricciones[i].valor;
    }

    // --- Bucle principal del algoritmo Simplex ---
    while (true)
    {
        // 2. Seleccionar la columna pivote (el valor mas negativo en la fila Z)
        int col_pivote = -1;
        double min_val = 0.0;
        for (int j = 0; j < num_cols - 1; ++j)
        {
            if (tabla[0][j] < min_val)
            {
                min_val = tabla[0][j];
                col_pivote = j;
            }
        }
        if (col_pivote == -1 || min_val >= -EPSILON)
        {
            break;
        }

        // 3. Seleccionar la fila pivote
        int fila_pivote = -1;
        double min_cociente = std::numeric_limits<double>::max();
        for (int i = 1; i < num_rows; ++i)
        {
            if (tabla[i][col_pivote] > EPSILON)
            {
                double cociente = tabla[i][num_cols - 1] / tabla[i][col_pivote];
                if (cociente < min_cociente)
                {
                    min_cociente = cociente;
                    fila_pivote = i;
                }
            }
        }
        if (fila_pivote == -1)
        {
            std::cout << "\n>> El problema no esta acotado.\n";
            sol.solucionEncontrada = false;
            return;
        }

        // 4. Realizar operaciones de fila
        double pivote = tabla[fila_pivote][col_pivote];
        for (int j = 0; j < num_cols; ++j)
        {
            tabla[fila_pivote][j] /= pivote;
        }

        for (int i = 0; i < num_rows; ++i)
        {
            if (i != fila_pivote)
            {
                double factor = tabla[i][col_pivote];
                for (int j = 0; j < num_cols; ++j)
                {
                    tabla[i][j] -= factor * tabla[fila_pivote][j];
                }
            }
        }
    }

    // 5. Extraer la solucion optima
    sol.x1 = 0.0;
    sol.x2 = 0.0;

    for (int j = 0; j < num_vars; ++j)
    {
        int count_ones = 0;
        int row_with_one = -1;
        for (int i = 1; i < num_rows; ++i)
        {
            if (std::abs(tabla[i][j] - 1.0) < EPSILON)
            {
                count_ones++;
                row_with_one = i;
            }
            else if (std::abs(tabla[i][j]) > EPSILON)
            {
                row_with_one = -1;
                break;
            }
        }
        if (count_ones == 1 && row_with_one != -1)
        {
            if (j == 0)
            {
                sol.x1 = tabla[row_with_one][num_cols - 1];
            }
            else if (j == 1)
            {
                sol.x2 = tabla[row_with_one][num_cols - 1];
            }
        }
    }

    sol.gananciaMaxima = tabla[0][num_cols - 1];
    sol.solucionEncontrada = true;

    std::cout << "Solucion optima encontrada:\n";
    std::cout << "  - Numero de mesas (x1) = " << sol.x1 << "\n";
    std::cout << "  - Numero de sillas (x2) = " << sol.x2 << "\n";
    std::cout << "  - Ganancia maxima (Z) = $" << sol.gananciaMaxima << std::endl;
}