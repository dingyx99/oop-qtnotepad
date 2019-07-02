#include "box.h"
#include "ui_box.h"



box::box(QWidget *parent) :
    QTextEdit(parent),
    ui(new Ui::box)
{
    ui->setupUi(this);
}

box::~box()
{
    delete ui;
}

void box::creatFile()
{
    static int number = 1;
    QString str = QString("文档%1").arg(number);
    number++;
    this->setWindowTitle(str);
}
