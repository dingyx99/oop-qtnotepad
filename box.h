#ifndef BOX_H
#define BOX_H

#include <QWidget>
#include<QTextEdit>
#include <QTextStream>
#include <QFile>
#include <qfiledialog.h>
#include <QMessageBox>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QPrinter>
#include <QColorDialog>
#include <QCloseEvent>

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
    void setFileContent(QString);
    QString getFileContent();

    void creatFile();
    void saveFileAs();
    void saveFile();
    void printFile();
    void printFileView();
    void setBold();
    void setItalic();
    void setUnderline();
    void setColor();
    void copyText();
    void cutText();
    void pasteText();
    void unsetBold();
    void maybeSave();
    void closeEvent(QCloseEvent *event);



private:
    Ui::box *ui;

    QString filePath;  //保存打开文档的路径
    QString fileContent;   //剪切板
    void mergeFormat(QTextCharFormat format);

};

#endif // BOX_H
