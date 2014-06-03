#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdlib>
#include <QWidget>
#include <QMenu>
#include <QMessageBox>
#include <QDebug>
#include "aboutauthors.h"
#include "technicalsupport.h"
#include "exercises.h"
#include "equation.h"
#include "base.h"
#include "matrix.h"
#include "resultmatrix.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    this->setWindowTitle("Kalkulator Macierzy v1.0"); //ustawienie tytułu głównego okna
    ui->setupUi(this);

    ui->result->setReadOnly(true); //ustawienie pola result na "tylko do odczytu"

    ui->horizontalSliderAX->setRange(0, 6);
    ui->horizontalSliderAX->setSingleStep(1);
    ui->horizontalSliderAX->setTickInterval(1);
    ui->horizontalSliderAX->setTickPosition(QSlider::TicksBelow);
    ui->labelAX->setText("0");

    ui->horizontalSliderAY->setRange(0, 6);
    ui->horizontalSliderAY->setSingleStep(1);
    ui->horizontalSliderAY->setTickInterval(1);
    ui->horizontalSliderAY->setTickPosition(QSlider::TicksBelow);

    ui->horizontalSliderBX->setRange(0, 6);
    ui->horizontalSliderBX->setSingleStep(1);
    ui->horizontalSliderBX->setTickInterval(1);
    ui->horizontalSliderBX->setTickPosition(QSlider::TicksBelow);

    ui->horizontalSliderBY->setRange(0, 6);
    ui->horizontalSliderBY->setSingleStep(1);
    ui->horizontalSliderBY->setTickInterval(1);
    ui->horizontalSliderBY->setTickPosition(QSlider::TicksBelow);

    ui->labelAX->setText("0");
    ui->labelAY->setText("0");
    ui->labelBX->setText("0");
    ui->labelBY->setText("0");

    b = new base(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_released()
{
    //pobranie wartości z pol ax, ay i zamiana na int
    //int ax = ui->ax->displayText().toInt();
    int ax = ui->horizontalSliderAX->value();
    int ay = ui->horizontalSliderAY->value();

    //pobranie wartości z pol bx, by i zamiana na int
    int bx = ui->horizontalSliderBX->value();
    int by = ui->horizontalSliderBY->value();
    Matrix * A = NULL, * B = NULL;

    if(!ui->a->toPlainText().isEmpty())
    {
        A = new Matrix(ui->a->toPlainText(), &ax, &ay); //utworzenie macierzy A
    }

    if(!ui->b->toPlainText().isEmpty())
    {
        B = new Matrix(ui->b->toPlainText(), &bx , &by); //utworzenie macierzy B
    }

    ResultMatrix * C = new ResultMatrix(); //utworzenie macierzy C, wynikowa
    Equation * eq = new Equation(); //obiekt będący reprezentacją działania wykonywanego na macierzach A i B

    //tablica wskaźników do funkcji klasy Equation

    ResultMatrix * (Equation::*chooseEquation[5]) (Matrix *, Matrix *) =
    {
        &Equation::addition,
        &Equation::multiplication,
        &Equation::determinant,
        &Equation::inverse,
        &Equation::transposition
    };

    ResultMatrix * chooseEquationTab[] =
    {
        (A && B && A->table && B->table) ? (eq->*chooseEquation[0])(A, B) : NULL, //A+B
        (A && B && A->table && B->table) ? (eq->*chooseEquation[1])(A, B) : NULL, //A*B
        (A && B && A->table && B->table) ? (eq->*chooseEquation[1])(B, A) : NULL, //B*A
        (A && A->table) ? (eq->*chooseEquation[2])(A, A) : NULL, //det(A)
        (B && B->table) ? (eq->*chooseEquation[2])(B, B) : NULL, //det(B)
        (A && A->table) ? (eq->*chooseEquation[3])(A,A) : NULL, //A^-1
        (B && B->table) ? (eq->*chooseEquation[3])(B,B) : NULL, //B^-1
        (A && A->table) ? (eq->*chooseEquation[4])(A, A) : NULL, //A^T
        (B && B->table) ? (eq->*chooseEquation[4])(B, B) : NULL //B^T

    };

    if(chooseEquationTab[ui->action->currentIndex()] != NULL)
    {
        C = chooseEquationTab[ui->action->currentIndex()]; //wykonanie funkcji realizującej działanie wybrane w comob box
    }

    //wydrukowanie macierzy wyniku jezeli została zwrócona, jeżeli nie drukujemy 0
    if(C->table)
    {
        QString sResult = "";

        //zamiana macierzy wynikowej na QString
        for(int y = 0; y < C->y; y++)
        {
            for(int x = 0; x < C->x; x++)
            {
                sResult+=QString::number(C->table[y][x])+" ";
            }
            sResult+="\n";
        }

        //ustawienie wyniku w oknie
        ui->result->setPlainText(sResult);

    } else if(C->simple_result)
    {
        //jeżeli wynik jest w postaci jednej liczby nie całej macierzy, np. wyznacznik lub rząd
         ui->result->setPlainText(QString::number(C->simple_result));
    }
        else
    {
        //jeżeli result = NULL to wypisujemy 0 - gdzieś wcześniej była niezgodność np.wymiarów
        ui->result->setPlainText(QString::number(0));
    }

    delete A;
    delete B;
    delete C;
    delete eq;
}

void MainWindow::on_actionAboutAuthors_triggered()
{
    aboutAuthors about(this);
    about.exec();
}

void MainWindow::on_actionStartExercise_triggered()
{
    Exercises exercise(this);
    exercise.exec();
}

void MainWindow::on_actionAddition_triggered()
{
    b->setItem(0);
    b->exec();
}

void MainWindow::on_actionMultiplication_triggered()
{

    b->setItem(1);
    b->exec();
}

void MainWindow::on_actionTransposition_triggered()
{
    b->setItem(2);
    b->exec();
}

void MainWindow::on_actionDeterminant_triggered()
{

    b->setItem(3);
    b->exec();
}

void MainWindow::on_actionMatrixInverse_triggered()
{
    b->setItem(4);
    b->exec();
}

void MainWindow::on_actionTechnicalSupport_triggered()
{
    technicalSupport support(this);
    support.exec();
}

void MainWindow::on_horizontalSliderAX_valueChanged(int value)
{
    ui->labelAX->setText(QString::number(ui->horizontalSliderAX->value()));
}

void MainWindow::on_horizontalSliderAY_valueChanged(int value)
{
    ui->labelAY->setText(QString::number(ui->horizontalSliderAY->value()));
}

void MainWindow::on_horizontalSliderBX_valueChanged(int value)
{
    ui->labelBX->setText(QString::number(ui->horizontalSliderBX->value()));
}

void MainWindow::on_horizontalSliderBY_valueChanged(int value)
{
    ui->labelBY->setText(QString::number(ui->horizontalSliderBY->value()));
}
