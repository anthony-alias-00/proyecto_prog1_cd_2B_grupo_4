#ifndef PROBLEMA_H
#define PROBLEMA_H

#include <vector>

struct Restriccion
{
    double coef_x1;
    double coef_x2;
    double valor;
};

struct DatosProblema
{
    double precio_x1 = 7.0; // Beneficio por mesa
    double precio_x2 = 5.0; // Beneficio por silla
    std::vector<Restriccion> restricciones;
};

void ingresarPrecios(DatosProblema &datos);
void ingresarRestricciones(DatosProblema &datos);
void definirFuncionObjetivo(const DatosProblema &datos, bool preciosIngresados);

#endif // PROBLEMA_H