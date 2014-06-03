#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "equation.h"
#include <QMainWindow>
#include "base.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool step_by_step;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    base * b;

private slots:
    void on_pushButton_released();

    void on_actionAboutAuthors_triggered();

    void on_actionStartExercise_triggered();

    void on_actionAddition_triggered();

    void on_actionMultiplication_triggered();

    void on_actionTransposition_triggered();

    void on_actionDeterminant_triggered();

    void on_actionMatrixInverse_triggered();

    void on_actionTechnicalSupport_triggered();

    void on_horizontalSliderAX_valueChanged(int value);

    void on_horizontalSliderAY_valueChanged(int value);

    void on_horizontalSliderBX_valueChanged(int value);

    void on_horizontalSliderBY_valueChanged(int value);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
