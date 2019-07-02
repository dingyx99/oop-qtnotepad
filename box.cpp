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
