#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QEvent>
#include <QPointer>
#include <QPlainTextEdit>
#include <QString>
#include <QTextCursor>
#include <QMessageBox>
#include <QLineEdit>

class findDialog : public QDialog
{
    Q_OBJECT

public:
    findDialog(QWidget *parent = nullptr, QPlainTextEdit *ptext = nullptr);
    bool event(QEvent *event);
    void setPlainTextEdit(QPlainTextEdit *ptext);
    QPlainTextEdit* getPlainTextEdit();

protected slots:
    void onFind();
    void onCancel();

protected:
    QGridLayout fLayout;
    QHBoxLayout fHBLayout;

    QLabel fLabel;
    QLineEdit fEdit;
    QPushButton findButton;
    QPushButton cancelButton;
    QCheckBox fCheck;
    QRadioButton forwardRatio;
    QRadioButton backRatio;

    QGroupBox fRadioGroup;

    QPointer<QPlainTextEdit> fTextEdit;
};

#endif // FINDDIALOG_H
