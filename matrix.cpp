#include "matrix.h"
#include <QStringList>
#include <QDebug>
#include <cmath>

Matrix::Matrix() {}

Matrix::Matrix(QString matrixInString, int * mx, int * my)
{
    x = *mx;
    y = *my;

    if(matrixInString != "")
    {
        table = intToMatrix(matrixInString);
    }
}

Matrix::Matrix(int *mx, int *my)
{
    x = *mx;
    y = *my;
    table = getRandomTable();
}

/*funkcja odpowiedzialna za konwersję macierzy w postaci QString na int
 * @param toMatrix wskaźnik to macierzy, do której zostanie zapisanamacierz w int
 * @param sMatrix macierz w postaci QString, ktora bedziemy konwertowac
 * */
double ** Matrix::intToMatrix(QString sMatrix)
{
    int i = 0; //zmienna pomocnicza, liczni głównej petli while

    //generacja macierzy o y wierszach i x kolumnach
    double **matrix = reinterpret_cast<double**>(new double[this->y]);
    for (int z = 0; z < this->y; z++)
    {
       matrix[z] = reinterpret_cast<double*>(new double[this->x]);
    }

    //tworzymy listę , ktora jest wypełniona elementami sMatrix
    QStringList listMatrix = sMatrix.split(QRegExp("\\s+"));

    //wypisanie elementów listy do konkretnych miejsc macierzy
    for(int y = 0; y < this->y; y++)
    {
        for(int x = 0; x < this->x; x++)
        {
            if(this->y * this->x == listMatrix.size()) //sprawdzamy czy zdeklarowane wymiary macierzy zgadzaja sie
            {
                matrix[y][x] = listMatrix[i].toDouble();
            } else {
                return NULL;
            }

            i++;
        }
    }

    return matrix; //zwrócenie gotowej macierzy
}

//funkcja uzupełniająca macierz w losową tablicę
double ** Matrix::getRandomTable()
{
    int matrixHigh = 10;
    int matrixLow = 0;

    double **matrix = reinterpret_cast<double**>(new double[this->y]);
    for (int z = 0; z < this->y; z++)
    {
       matrix[z] = reinterpret_cast<double*>(new double[this->x]);
    }

    for(int y = 0; y < this->y; y++)
    {
        for(int x = 0; x < this->x; x++)
        {
            matrix[y][x] = qrand() % ((matrixHigh + 1) - matrixLow) + matrixLow;
        }
    }

    return matrix;
}
