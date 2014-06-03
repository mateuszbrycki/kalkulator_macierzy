#include "technicalsupport.h"
#include "ui_technicalsupport.h"

technicalSupport::technicalSupport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::technicalSupport)
{
    ui->setupUi(this);
    this->setWindowTitle("Wsparcie techniczne");
}

technicalSupport::~technicalSupport()
{
    delete ui;
}

void technicalSupport::on_pushButton_released()
{
    this->close();
}
