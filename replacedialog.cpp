#include "ReplaceDialog.h"

ReplaceDialog::ReplaceDialog(QWidget* parent, QPlainTextEdit* ptext)
    :FindDialog(parent, ptext)
{
    m_replacelabel.setText("替换为(P):");
    m_replacebutton.setText("替换(&R)");
    m_replaceallbutton.setText("全部替换(&A)");

    m_layout.removeWidget(&m_check);
    m_layout.removeWidget(&m_radiogroup);
    m_layout.removeWidget(&m_cancelbutton);

    m_layout.addWidget(&m_replacelabel, 1, 0);
    m_layout.addWidget(&m_replaceedit, 1, 1);
    m_layout.addWidget(&m_replacebutton, 1, 2);

    m_layout.addWidget(&m_check, 2, 0);
    m_layout.addWidget(&m_radiogroup, 2, 1);
    m_layout.addWidget(&m_replaceallbutton, 2, 2);

    m_layout.addWidget(&m_cancelbutton, 3, 2);
    //setLayout(&m_layout);

    setWindowTitle("替换");

    connect(&m_replacebutton, SIGNAL(clicked()), this, SLOT(onReplace()));
    connect(&m_replaceallbutton, SIGNAL(clicked()), this, SLOT(onRepalceAll()));
}

void ReplaceDialog::onReplace()
{
    QString target = m_edit.text();
    QString to = m_replaceedit.text();
    if((m_textedit != nullptr) && (target != nullptr) && (to != nullptr))
    {
        QString select = m_textedit->textCursor().selectedText();
        if(select == target)
        {
            m_textedit->insertPlainText(to);
        }
        onFind();
    }
}

void ReplaceDialog::onRepalceAll()
{
    QString target = m_edit.text();
    QString to = m_replaceedit.text();
    if((m_textedit != nullptr) && (target != nullptr) && (to != nullptr))
    {
        QString text = m_textedit->toPlainText();
        text.replace(target, to, m_check.isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
        m_textedit->clear();
        m_textedit->insertPlainText(text);
    }
}
