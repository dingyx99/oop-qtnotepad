#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QPixmap>
#include <QPalette>

class aboutDialog : public QDialog
{
    Q_OBJECT
public:
    aboutDialog(QWidget* parent = nullptr);

private slots:
    void onClose();

private:
    QLabel logoLabel;
    QPlainTextEdit infoText;
    QPushButton closeButton;
};

#endif // ABOUTDIALOG_H
