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

void box::setFilePath(QString filepath){
    filePath = filepath;
}
QString box::getFilePath(){
    return filePath;
}
//void box::setFileContent(QString filecontent){
//    fileContent = filecontent;
//}
//QString box::getFileContent(){
//    return fileContent;
//}

void box::creatFile()
{
    static int number = 1;
    QString str = QString("文档%1").arg(number);
    number++;
    this->setWindowTitle(str);
    filePath = "";
}

void box::saveFileAs()
{
    QString filepath = QFileDialog::getSaveFileName(this, "另存为",
                                   "未命名文档", "eXtensible Markup Language File(*.xml)");
    if(filepath == "")
    {
        QMessageBox::warning(this, "warning", "文件无保存路径");
        return;
    }

    QFile file;
    file.setFileName(filepath);
    if(!file.open(QIODevice::WriteOnly)){     //打开文档
        QMessageBox::warning(this, "waring", "没有成功打开文档");
        return;
    }
    QTextStream out(&file);
    QString str = this->toPlainText();  //提取文档内容
    out << str;     //把文档内容写入新建文档
    QMessageBox::information(this, "提示", "文档保存成功");
    file.close();    //关闭文档

//    QByteArray  strBytes = str.toUtf8();     第二种写入方式
//    file.write(strBytes,strBytes.length());
//    file.close();
}

void box::saveFile()
{
    QFile file(filePath);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    QString str = this->toPlainText();
    out << str;
    QMessageBox::information(this, "提示", "文档保存成功");
    file.close();
}

void box::printFile()
{
    //QPrinter printer;

}
