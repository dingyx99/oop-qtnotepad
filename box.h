#ifndef BOX_H
#define BOX_H

#include <QWidget>
#include<QTextEdit>
#include <QTextStream>
#include <QFile>
#include <qfiledialog.h>
#include <QMessageBox>
#include <QtPrintSupport/QPrintDialog>

namespace Ui {
class box;
}

class box : public QTextEdit
{
    Q_OBJECT

public:
    explicit box(QWidget *parent = nullptr);
    ~box();
    void setFilePath(QString);
    QString getFilePath();
//    void setFileContent(QString);
//    QString getFileContent();

    void creatFile();
    void saveFileAs();
    void saveFile();
    void printFile();

private:
    Ui::box *ui;

    QString filePath;  //保存打开文档的路径
   // QString fileContent;

};

#endif // BOX_H
