#include "exercises.h"
#include "ui_exercises.h"
#include "matrix.h"
#include "equation.h"
#include "resultmatrix.h"
#include <QGlobal.h>
#include <QTime>
#include <QStringList>
#include <QMessageBox>

Exercises::Exercises(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Exercises)
{
    ui->setupUi(this);
    this->setWindowTitle("Tryb ćwiczeń");

    //a i b tylko do odczytu
    ui->a->setReadOnly(true);
    ui->b->setReadOnly(true);

    Matrix * A = NULL;
    Matrix * B = NULL;
    ResultMatrix * C = NULL;
    Equation * eq = new Equation(); //obiekt będący reprezentacją działania wykonywanego na macierzach A i B

    newExcercise(); //wywołanie nowego działania

}

void Exercises::newExcercise()
{
     //losujemy działanie z tabeli wskazników
     int low = 0;
     int high = 4;

     int randomEquation = qrand() % ((high + 1) - low) + low; //losowanie działania do wykonania

     //następnie według warunków zadania losujemy dwie lub jedną macierz
     //dodawanie - takie same wymiary
     //mnożenie liczba kolumn A = liczba wierszy B
     //wyznacznik macierz kwadratowa
     //transpozycja - bez znaczenia

     //graniczne wymiary macierzy do rozwiazania
     int matrixLow = 4;
     int matrixHigh = 6;

     int x = qrand() % ((matrixHigh + 1) - matrixLow) + matrixLow; //losujemy pierwszy wymiar

     if(randomEquation == 0)
     {//dodawanie
         int y = qrand() % ((matrixHigh + 1) - matrixLow) + matrixLow;

         A = new Matrix(&x, &y);
         B = new Matrix(&x, &y);

         ui->task->setPlainText("Dane są dwie macierze A i B. Należy obliczyć sumę tych macierzy, a wynik wpisać w odpowiednim miejscu.");

     } else if(randomEquation == 1)
     {//mnożenie
         int y = qrand() % ((matrixHigh + 1) - matrixLow) + matrixLow;
         int z = qrand() % ((matrixHigh + 1) - matrixLow) + matrixLow;

         A = new Matrix(&x, &y);
         B = new Matrix(&z, &x);

         ui->task->setPlainText("Dane są dwie macierze A i B. Należy obliczyć iloczyn tych macierzy, a wynik wpisać w odpowiednim miejscu.");

     } else if(randomEquation == 2)
     {//wyznacznik
         A = new Matrix(&x, &x);

         ui->task->setPlainText("Dana jest macierz A. Należy obliczyć wyznacznik tej macierzy, a wynik wpisać w odpowiednim miejscu.");
     } else if(randomEquation == 3)
     {//transpozycja
         int y = qrand() % ((matrixHigh + 1) - matrixLow) + matrixLow;
         A = new Matrix(&x, &y);

         ui->task->setPlainText("Dana jest macierz A. Należy dokonać transpozycji tej macierzy, a wynik wpisać w odpowiednim miejscu.");
     }
	else if(randomEquation == 4)
	{//macierz odwrotna
        A = new Matrix(&x, &x);

        ui->task->setPlainText("Dana jest macierz A. Należy wyznaczyć macierz odwrotną do macierzy, a wynik wpisać w odpowiednim miejscu.");
    }


    ResultMatrix * (Equation::*chooseEquation[5]) (Matrix *, Matrix *) =
    {
         &Equation::addition,
         &Equation::multiplication,
         &Equation::determinant,
         &Equation::transposition,
         &Equation::inverse
    };

    ResultMatrix * chooseEquationTab[] =
    {
        (A && B) ? (eq->*chooseEquation[0])(A, B) : NULL, //A+B
        (A && B) ? (eq->*chooseEquation[1])(A, B) : NULL, //A*B
        (A) ? (eq->*chooseEquation[2])(A, A) : NULL, //det(A)
        (A) ? (eq->*chooseEquation[3])(A, A) : NULL, //A^T
        (A) ? (eq->*chooseEquation[4])(A, A) : NULL //A^-1
    };

     if(chooseEquationTab[randomEquation] != NULL)
     {
         C = chooseEquationTab[randomEquation];
     }

     if(A)
     {
        printMatrix(A); //wypisanie macierzy A i B do odpowiednich pól
     }
     if(B)
     {
         printMatrix(B);
     }

     //aby drukować wynik => print(C)
}

//funkcja wypisująca macierz w formularzu
void Exercises::printMatrix(Matrix * matrix)
{
    if(matrix->table)
    {
        QString sResult = "";

        //zamiana macierzy wynikowej na QString
        for(int y = 0; y < matrix->y; y++)
        {
            for(int x = 0; x < matrix->x; x++)
            {
                sResult+=QString::number(matrix->table[y][x])+" ";
            }
            sResult+="\n";
        }

        if(matrix == A)
        {
        //ustawienie wyniku w oknie
            ui->a->setPlainText(sResult);
        } else if(matrix == B)
        {
            ui->b->setPlainText(sResult);
        } else if(matrix == C)
        {
          ui->result->setPlainText(sResult);
        }
    }
}

//funkcja sprawdzająca czy macierz wpisywana przez użytkownika jest taka sama jak wynik działania
void Exercises::on_check_released()
{
     //pobranie z formularza odpowiedzi użytkownika
     QString userResult = ui->result->toPlainText();

     //rozdzielamy macierz wpisaną przez użytkownika po białych znakach
     QStringList userResultList = userResult.split(QRegExp("\\s+"));

     QString sResult = "";

    //zamiana macierzy wynikowej (C) na QString
    for(int y = 0; y < C->y; y++)
    {
        for(int x = 0; x < C->x; x++)
        {
            sResult+=QString::number(C->table[y][x])+" ";
        }
        sResult+="\n";
    }
    //rozdzielenie macierzy wynikowej (C) po białych znakach
    QStringList resultList = sResult.split(QRegExp("\\s+"));

    bool same; //zmienna syganalizująca czy ciągi są równe

    if(resultList.length() == userResultList.length()) //sprawdzanie czy długości obu list są równe
    {
        for(int x = 0; x < resultList.length(); ++x)
        {
            if(resultList[x] != userResultList[x]) //jeżeli elementy na tym samym miejscu w obu listach są różne elementy
            {
                same = false; //są różnie więc ustawiamy false
                break; //kończymy
            } else {
                same = true; //są takie same więc true
            }
        }
    } else {
        same = false; //jeżeli listy nie mają takich samych długości to na pewno są różne
    }

    QString answer;
    if(same)
    {
        answer = "Podana odpowiedź jest prawidłowa! Czy chcesz rozwiązać kolejne zadanie?";
    } else {
        answer = "Podana odpowiedź jest nieprawidłowa! Czy chcesz rozwiązać kolejne zadanie?";
    }

    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(this, "Wynik", answer, QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        //ustawienie adresów macierzy na NULL
        A = NULL;
        B = NULL;
        C = NULL;

        //wyczyszczenie pól formularza
        ui->a->setPlainText("");
        ui->b->setPlainText("");
        ui->result->setPlainText("");

        //generowanie nowego zadania
        newExcercise();
    }
}

Exercises::~Exercises()
{
    delete ui;
}
