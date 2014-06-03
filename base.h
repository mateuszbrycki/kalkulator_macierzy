#ifndef BASE_H
#define BASE_H

#include <QDialog>
#include <QString>
#include <QTreeWidgetItem>

namespace Ui {
class base;
}

class base : public QDialog
{
    Q_OBJECT



public:
    QList<QTreeWidgetItem * > items;

    explicit base(QWidget *parent = 0);

    QTreeWidgetItem * addRoot(QString name);
    QTreeWidgetItem * addChild(QTreeWidgetItem * root, QString childImg, int height);
    void setItem(int number);

    ~base();

private:
    Ui::base *ui;
};

#endif // BASE_H
