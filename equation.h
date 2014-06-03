#ifndef EQUATION_H
#define EQUATION_H
#include <QString>
#include <QDebug>
#include "matrix.h"
#include "resultmatrix.h"

//klasa będąca reprezentacją działań na macierzach
class Equation
{
public:

    Equation() {}
    ResultMatrix * addition(Matrix * first, Matrix * second); //dodawanie macierzy
    ResultMatrix * multiplication(Matrix * first, Matrix * second); //mnożenie macierzy
    ResultMatrix * determinant(Matrix * first, Matrix * second = NULL); //obliczanie wyznacznika macierzy
    ResultMatrix * transposition(Matrix * first, Matrix * second = NULL); //generowanie macierzy transponowanej
    ResultMatrix * inverse(Matrix * first, Matrix * second = NULL);
private:
    double ** getResultTable(Matrix * first); //funkcja odpowiedzialna za genreowanie elementu table macierzy wynikowej C
    bool LU(Matrix * first); //funkcja realizująca rozkład LU macierzy first za pomocą algorytmu Doolitle'a
    bool LU_solve(Matrix * first, double ** X, int k);

};

#endif // EQUATION_H
