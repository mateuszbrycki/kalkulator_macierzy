#ifndef TECHNICALSUPPORT_H
#define TECHNICALSUPPORT_H

#include <QDialog>

namespace Ui {
class technicalSupport;
}

class technicalSupport : public QDialog
{
    Q_OBJECT

public:
    explicit technicalSupport(QWidget *parent = 0);
    ~technicalSupport();

private slots:
    void on_pushButton_released();

private:
    Ui::technicalSupport *ui;
};

#endif // TECHNICALSUPPORT_H
