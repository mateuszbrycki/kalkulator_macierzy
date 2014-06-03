#ifndef MATRIX_H
#define MATRIX_H
#include <QString>

class Matrix
{
public:
    int x = 0;
    int y = 0;
    double ** table = NULL;

    Matrix();
    Matrix(int * mx, int * my);
    Matrix(QString matrixInString, int * mx, int * my);

private:
    double ** intToMatrix(QString sMatrix); //konwersja macierzy z QString na int
    double ** getRandomTable();
};

#endif // MATRIX_H
