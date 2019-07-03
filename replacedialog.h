#ifndef REPLACEDIALOG_H
#define REPLACEDIALOG_H

#include "finddialog.h"

//Function with bugs


class replaceDialog : public findDialog
{
    Q_OBJECT

public:
    replaceDialog(QWidget* parent = nullptr, QPlainTextEdit* pText = nullptr);

protected:
    QLabel replaceLabel;
    QLineEdit replaceEdit;
    QPushButton replaceButton;
    QPushButton replaceAllButton;

protected slots:
    void onReplace();
    void onReplaceAll();
};

#endif // REPLACEDIALOG_H
