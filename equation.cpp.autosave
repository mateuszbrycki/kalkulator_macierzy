#include "equation.h"
#include <QString>
#include <QDebug>
#include <cmath>

/*funkcja odpowiedzialna za dodanie macierzy
 * @param first pierwszy składnik dodawania
 * @param second drugi składnik dodawania
 **/
ResultMatrix * Equation::addition(Matrix * first, Matrix * second)
{
     ResultMatrix * C = new ResultMatrix;
    //sprawdzenie czy obie macierze maja takie same wymiary - warunek dodawania macierzy
    if ((first->x == second->x) && (first->y == second->y))
    {
        C->x = first->x; //ustawienie ilosci kolumn macierzy wynikowej
        C->y = first->y; //ustawienie ilosci wierszy macierzy wynikowej

        //dynamiczna tablica na wyniki
        C->table = getResultTable(C);

        //obliczanie sumy macierzy first oraz second
        for (int y = 0; y < C->y; y++)
        {
            for (int x = 0; x < C->x; x++)
            {
                C->table[y][x] = first->table[y][x] + second->table[y][x];
            }
        }
    }

    return C;
}

/*funkcja odpowiedzialna za wykonywanie mnożenia macierzy
 * @param first pierwszy czynnik iloczynu
 * @param second drugi czynnik iloczynu
 * pamiętaj, A * B != B * A!!
 * */
ResultMatrix * Equation::multiplication(Matrix * first, Matrix * second)
{
    ResultMatrix * C = new ResultMatrix;

    if(first->x == second->y) //sprawdzamy czy ilości kolumn w macierzy A są równe ilości wierszy macierzy B - warunek mnożenia
    {
        //przy mnożeniu macierzy A*B macierz wynikowa ma tyle samo wierszy co macierz A, oraz tyle samo kolumn co B
        C->x = second->x; //kolumny
        C->y = first->y; //wiersze

        C->table = getResultTable(C);

        //pętla odpowiedzialna za wykonywanie mnożenia poszczególnych elementów macierzy
        for (int i = 0; i < first->y; i++)
        {
            for(int j = 0; j < second->x; j++)
            {
                int s = 0; //zmienna pomocnicza na sumy obliczane w kolejnych krokach
                for(int k = 0; k < first->x; k++)
                {
                    s += first->table[i][k] * second->table[k][j];
                }
                C->table[i][j] = s; //przypisanie tablicy wynikowej wartości
            }
        }
    }
    return C;
 }
/*funkcja odpowiedzialna za obliczenie wyznacznika macierzy first
 * @param first macierz, ktorej wyznacznik bedziemy obliczac
 * @param sedond niby macierz, ale ustawiamy na null, aby funkcje moznabylo wywolac z jednym argumentem, a tym samym funkcja miala dwa argumenty - jeden domniemany
 * takie rozwiazanie pozwoli nam uzywac tego samego wskaznika do funkcji klasy dla wszystkich metod klasy Equation
 * */
ResultMatrix * Equation::determinant(Matrix * first, Matrix * second)
{
    //pomocniczy obiekt, na którym będziemy pracować, aby nie stracić tablicy w obiekcie first
    Matrix * temp = new Matrix(&first->x, &first->y);

    //utworzenie tablicy obiektu tymczasowego
    temp->table = getResultTable(temp);

    //kopiowanie tablicy
    for(int i = 0; i < temp->y; i++)
    {
        for(int j = 0; j < temp->x; j++)
        {
            temp->table[i][j] = first->table[i][j];
        }
    }

    ResultMatrix * C = new ResultMatrix; //obiekt, który zostanie zwrócony
    if(first->x == first->y) //macierz jest kwadratowa
    {
        if(LU(temp)) //dokonujemy rozkładu LU macierzy temp, jeżeli się powiódł, właśnie po to jest potrzebna macierz temp,
                    //metoda LU dokonuje zmian na przesłanej macierzy więc aby nie utracić (do dalszych obliczeń) tab z first wrzucamy temp
        {
            C->simple_result = temp->table[0][0]; //wyznacznik ustawiamy na element [0][0] macierzy

            for(int i = 1; i < temp->x; i++) //w kolejnych krokach obliczamy wyznacznik
            {
                C->simple_result *= temp->table[i][i]; //zapisujemy wyznacznik macierzy do wyniku
            }
        }
    }
    return C;
}

/*funkcja odpowiedzialna za wykonanie transpozycji macierzy
 * @param first macierz, ktorej transpozycje bedziemy wykonywac
 * @param second j/w domyslnie ustawiona na NULL
 * */
ResultMatrix * Equation::transposition(Matrix * first, Matrix * second)
{

    ResultMatrix * C = new ResultMatrix; //obiekt, który zostanie zwrócony

    //uzupełnianie obiektu macierzy wynikowej
    C->x = first->y;
    C->y = first->x;
    C->table = getResultTable(C);

    //zamiana wierszy z kolumnami
    for(int y = 0; y < first->x; y++)
    {
        for(int x = 0; x < first->y; x++)
        {
            C->table[y][x] = first->table[x][y];
        }
    }

    return C;
}

/* Funkcja odpowiedzialna za tworzenie macierzy odwrotnej
 *  macierz first to macierz, której macierz odwrotną bedzie obliczać funkcja
 *  second dajemy na NULL
 * */

ResultMatrix * Equation::inverse(Matrix *first, Matrix *second)
{
    ResultMatrix * C = new ResultMatrix;

    //pomocniczy obiekt, na którym będziemy pracować, aby nie stracić tablicy w obiekcie first
    Matrix * temp = new Matrix(&first->x, &first->y);

    //utworzenie tablicy obiektu tymczasowego
    temp->table = getResultTable(temp);

    //kopiowanie tablicy
    for(int i = 0; i < temp->y; i++)
    {
        for(int j = 0; j < temp->x; j++)
        {
            temp->table[i][j] = first->table[i][j];
        }
    }

    if(first->x == first->y)
    {
        //uzupełnianie obiektu macierzy wynikowej
        C->x = first->y;
        C->y = first->x;
        C->table = getResultTable(C);

        double **X;
        int i, j;
        bool ok;

        X = new double *[first->x];

         for(i = 0; i < first->x; i++)
         {
              X[i] = new double [first->x];
         }

         //wykonujemy rozklad LU macierzy temp (czyli first)
         if(LU(temp))
         {
             //tworzymy macierz jednostkową X
             for(i = 0; i < first->x; i++)
             {
               for(j = 0; j < first->x; j++)
               {
                   X[i][j] = 0;
               }
                   X[i][i] = 1;
             }
             //wyznaczamy kolejne kolumny macierzy odwrotnej w X
              ok = true;
              for(i = 0; i < first->x; i++)
              {
                if(! LU_solve(temp,X,i))
                {
                  ok = false;
                  break;
                }
              }
          }
          else
         {
             ok = false;
         }

         if(ok)
         {
           for(i = 0; i < first->x; i++)
           {
             for(j = 0; j < first->x; j++)
             {
              C->table[i][j] = X[i][j];
             }
           }
         }
         else
         {
             return false;
         }

         for(i = 0; i < first->x; i++)
         {
           delete [] X[i];
         }
         delete [] X;

    }

    return C;
}

/*funkcja odpowiedzialna za wygenerowanie tabeli składowej elementu C
 * @param C obiekt macierzy, ktorej tablicę będzimey generować
*/
double ** Equation::getResultTable(Matrix * first)
{
    //dynamiczna tablica na wyniki
    double ** table = reinterpret_cast<double**>(new double[first->y]);
    for (int y = 0; y < first->y; y++)
    {
        table[y] = reinterpret_cast<double *>(new double[first->x]);
    }

    return table;
}


/*funkcja realizująca rozkład LU za pomocą algorytmu Doolitle'a
 * @param first macierz, której rozkład LU będzie realizowany
*/
bool Equation::LU(Matrix * first)
{
    const double eps = 1e-12;

    //algorytm Doolitle'a
    for(int k = 0; k < first->x - 1; k++)
    {
        if(fabs(first->table[k][k]) < eps)
        {
            return false;
        }

        for(int i = k + 1; i < first->x; i++)
        {
            first->table[i][k] /= first->table[k][k];
        }

        for(int i = k + 1; i < first->x; i++)
        {
            for(int j = k + 1; j < first->x; j++)
            {
                first->table[i][j] -= first->table[i][k] * first->table[k][j];
            }
        }
    }
    return true;
}

/* Funkcja LU solve
 * macierz X to macierz jednostkowa potrzebna do wyznaczenia macierzy odwrotnej
 * */

bool Equation::LU_solve(Matrix * first, double **X, int k)
{
    const double eps = 1e-12;
    double s;
    int i, j;

    for(i = 1; i < first->x; i++)
       {
        s = 0;

            for(j = 0; j < i; j++ )
            {
              s += first->table[i][j] * X[j][k];
            }

        X[i][k]-= s;
       }

    if(fabs(first->table[first->x - 1][first->x - 1]) < eps)
    {
        return false;
    }

        X[first->x - 1][k] /= first->table[first->x - 1][first->x - 1];

        for(i = first->x - 2; i >= 0; i--)
        {
            s = 0;

            for(j = i + 1; j < first->x; j++)
            {
                s += first->table[i][j] * X[j][k];
            }

            if(fabs(first->table[i][i]) < eps) //sprawdzenie warunku
            {
                return false;
            }

            X[i][k] = (X[i][k] - s) / first->table[i][i];
        }
        return true;
}
