#ifndef SIMPLEX_H
#define SIMPLEX_H

#include "problema.h"

struct SolucionOptima
{
    double x1 = 0.0;
    double x2 = 0.0;
    double gananciaMaxima = 0.0;
    bool solucionEncontrada = false;
};

void calcularSolucionOptima(const DatosProblema &datos, SolucionOptima &sol, bool precios, bool restricciones);

#endif // SIMPLEX_H