#ifndef ABOUTAUTHORS_H
#define ABOUTAUTHORS_H

#include <QDialog>

namespace Ui {
class aboutAuthors;
}

class aboutAuthors : public QDialog
{
    Q_OBJECT

public:
    explicit aboutAuthors(QWidget *parent = 0);
    ~aboutAuthors();

private slots:
    void on_pushButton_released();

private:
    Ui::aboutAuthors *ui;
};

#endif // ABOUTAUTHORS_H
