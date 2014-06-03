#include "base.h"
#include "ui_base.h"
#include <QWidget>
#include <QPlainTextEdit>
#include <QTreeWidgetItem>
#include <QBrush>
#include <QPixmap>
#include <QImage>
#include <QLabel>
#include <QDebug>
#include <QIcon>

base::base(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::base)
{
    ui->setupUi(this);

    setWindowTitle("Teoria działań na macierzach");

    QTreeWidgetItem * addition = addRoot("Dodawanie");
    QTreeWidgetItem * additionChild = addChild(addition, ":/images/addition.jpg", 486);
    //additionChild->setBackground(0, QBrush(additionImg));
    items.push_back(additionChild);


    QTreeWidgetItem * multiplication = addRoot("Mnożenie");
    QTreeWidgetItem * multiplicationChild = addChild(multiplication, ":/images/multiplication.jpg", 456);
    items.push_back(multiplicationChild);

    QTreeWidgetItem * transpozition = addRoot("Transpozycja");
    QTreeWidgetItem * transpozitionChild = addChild(transpozition, ":/images/transposition.jpg", 508);
    items.push_back(transpozitionChild);

    QTreeWidgetItem * determinant = addRoot("Wyznacznik macierzy");
    QTreeWidgetItem * determinantChild = addChild(determinant, ":/images/determinant.jpg", 490);
    items.push_back(determinantChild);

    QTreeWidgetItem * inversion = addRoot("Macierz odwrotna");
    QTreeWidgetItem * inversionChild = addChild(inversion, ":/images/inversion.jpg", 780);
    items.push_back(inversionChild);

}

QTreeWidgetItem * base::addRoot(QString name)
{
    QTreeWidgetItem * root = new QTreeWidgetItem();
    ui->treeWidget->addTopLevelItem(root);
    root->setText(0, name);

    return root;
}

QTreeWidgetItem * base::addChild(QTreeWidgetItem * root, QString childImg, int height)
{
    QTreeWidgetItem * child = new QTreeWidgetItem;
    root->addChild(child);

    QPlainTextEdit * text = new QPlainTextEdit(ui->treeWidget);
    text->setReadOnly(true);
    //text->setPlainText(description);
    text->setStyleSheet("QPlainTextEdit {margin-left:0px; margin-right:40px; margin-top: 0px; margin-bottom: 0px; padding: 0px;}");
    text->setFixedHeight(height); //ustawienie rozmiarów pola tekstowego
    text->setFixedWidth(690);

    //dodawanie tła dla pola tekstowego
    QPalette* palette = new QPalette();
    palette->setBrush(QPalette::Base,*(new QBrush(QPixmap(childImg))));

    text->setPalette(*palette); //ustawienie tła
    text->setBaseSize(100, 100);
    ui->treeWidget->setItemWidget(child, 0, text);

    return child;
}

/*rozwiniecie konkretnego akapitu z tekstem
*@param number numer akapitu, ktory ma byc rozwiniety
* */
void base::setItem(int number)
{
    ui->treeWidget->setCurrentItem(items.at(number));
}

base::~base()
{
    delete ui;
}
