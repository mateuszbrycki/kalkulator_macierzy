#ifndef EXERCISES_H
#define EXERCISES_H
#include "resultmatrix.h"
#include "equation.h"

#include <QDialog>

namespace Ui {
class Exercises;
}

class Exercises : public QDialog
{
    Q_OBJECT

public:
    explicit Exercises(QWidget *parent = 0);
    void newExcercise();
    ~Exercises();

private slots:
    void on_check_released();

private:
    void printMatrix(Matrix * matrix);

    Ui::Exercises *ui;
    Matrix * A;
    Matrix * B;
    ResultMatrix * C;
    Equation * eq;
};

#endif // EXERCISES_H
