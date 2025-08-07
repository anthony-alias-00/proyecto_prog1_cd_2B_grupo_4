#include "grafico.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void mostrarGrafico(const DatosProblema &datos, const SolucionOptima &sol)
{
    if (!sol.solucionEncontrada)
    {
        std::cout << "\n>> Error: Primero debe calcular la solucion optima en la opcion 4.\n";
        return;
    }

    std::ofstream archivo("plot.plt");
    if (!archivo.is_open())
    {
        std::cerr << "Error: No se pudo crear el archivo de script para el grafico.\n";
        return;
    }

    std::cout << "\nGenerando script de Gnuplot y mostrando grafico...\n";

    archivo << "set terminal wxt enhanced font 'Arial,12' title 'Solucion de Optimizacion'\n";
    archivo << "set title 'Area Factible - Flair Furniture'\n";
    archivo << "set xlabel 'Numero de mesas (x1)'\n";
    archivo << "set ylabel 'Numero de sillas (x2)'\n";
    archivo << "set xrange [0:80]\n";
    archivo << "set yrange [0:110]\n";
    archivo << "set grid\n";
    archivo << "set key top left\n";

    // **CORRECCIÓN DEFINITIVA:** Se elimina el comando 'set object' problemático
    // y se usa una línea de 'plot' para dibujar la región rellena.
    archivo << "plot \\\n";
    archivo << "    (240.0 - 4.0*x) / 3.0 title '4x1 + 3x2 <= 240' with lines dashtype '-' lw 2 lc 'blue', \\\n";
    archivo << "    100.0 - 2.0*x title '2x1 + x2 <= 100' with lines dashtype '-' lw 2 lc 'green', \\\n";
    archivo << "    60 title 'x2 <= 60' with lines dashtype '-' lw 2 lc 'orange', \\\n";

    // Se agrega el polígono con 'filledcurves' al principio de la cadena
    archivo << "    '-' with filledcurves fs solid 0.2 fc 'blue' notitle, \\\n";

    archivo << "    '-' with points pt 7 ps 2 lc 'red' title 'Punto Optimo'\\\n";
    archivo << "    , '-' with labels offset char 1,1 font ',14' textcolor 'red' notitle\n";

    // Bloque de datos para la región sombreada
    archivo << "0 0\n";
    archivo << "60 0\n";
    archivo << "30 40\n";
    archivo << "0 60\n";
    archivo << "0 0\n";
    archivo << "e\n";

    // Bloque de datos para el punto óptimo y la etiqueta
    archivo << sol.x1 << " " << sol.x2 << "\n";
    archivo << "e\n";

    archivo << sol.x1 << " " << sol.x2 << " '(" << (int)sol.x1 << ", " << (int)sol.x2 << ")'\n";
    archivo << "e\n";

    archivo.close();

    system("gnuplot -p plot.plt");
}