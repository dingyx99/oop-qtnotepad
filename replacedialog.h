#ifndef REPLACEDIALOG_H
#define REPLACEDIALOG_H

#include "FindDialog.h"

class ReplaceDialog : public FindDialog
{
    Q_OBJECT
public:
    ReplaceDialog(QWidget* parent = nullptr, QPlainTextEdit* ptnullptrxt = nullptr);
    QString getReplaceEdit();

protected:

    QLabel m_replacelabel;
    QLineEdit m_replaceedit;
    QPushButton m_replacebutton;
    QPushButton m_replaceallbutton;

protected slots:
    void onReplace();
    void onRepalceAll();
    void sentToParent();
    void sentToParent_next();

signals:
    void parentReceive();
    void parentReceive_next();

};

#endif // REPLACEDIALOG_H
