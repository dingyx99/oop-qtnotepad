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
#include <QTextCharFormat>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

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
    void setPlain(int );
    void setColor();
    void copyText();
    void cutText();
    void pasteText();
    void setFont(QString);
    void setSize(double);
    void maybeSave();
    void closeEvent(QCloseEvent *event);
    QDialog* getFindDlg();


private slots:
    void on_action_findDlg_triggered();


private:
    Ui::box *ui;

    QString filePath;  //保存打开文档的路径
    QString fileContent;   //剪切板
    QDialog *findDlg;
    QLineEdit *findLineEdit;
    QPushButton *findBtn;

    void mergeFormat(QTextCharFormat format);

};

#endif // BOX_H
