#include "aboutauthors.h"
#include "ui_aboutauthors.h"

aboutAuthors::aboutAuthors(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutAuthors)
{
    ui->setupUi(this);
    this->setWindowTitle("O autorach");

}

aboutAuthors::~aboutAuthors()
{
    delete ui;
}

void aboutAuthors::on_pushButton_released()
{
    this->close();
}
