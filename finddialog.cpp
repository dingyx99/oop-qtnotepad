#include "finddialog.h"

findDialog::findDialog(QWidget *parent, QPlainTextEdit* ptext):QDialog (parent, Qt::WindowCloseButtonHint | Qt::Drawer)
{
    fLabel.setText("需要寻找的内容: ");
    findButton.setText("查找下一个(&F)");
    fCheck.setText("全字匹配(&C)");
    cancelButton.setText("取消");
    forwardRatio.setText("向上(&U)");
    backRatio.setText("向下(&D)");
    forwardRatio.setChecked(true);
    fRadioGroup.setTitle("方向");

    fHBLayout.addWidget(&forwardRatio);
    fHBLayout.addWidget(&backRatio);

    fRadioGroup.setLayout(&fHBLayout);

    fLayout.setSpacing(10);
    fLayout.addWidget(&fLabel, 0, 0);
    fLayout.addWidget(&fEdit, 0, 1);
    fLayout.addWidget(&findButton, 0, 2);
    fLayout.addWidget(&fCheck, 1, 0);
    fLayout.addWidget(&fRadioGroup, 1, 1);
    fLayout.addWidget(&cancelButton, 1, 2);

    setLayout(&fLayout);
    setWindowTitle("查找");
    setPlainTextEdit(ptext);

    connect(&findButton, SIGNAL(clicked()), this, SLOT(onFind()));
    connect(&cancelButton, SIGNAL(clicked()), this, SLOT(onCancel()));
}

void findDialog::setPlainTextEdit(QPlainTextEdit *ptext)
{
    fTextEdit = ptext;
}

QPlainTextEdit* findDialog::getPlainTextEdit()
{
    return fTextEdit;
}

void findDialog::onFind()
{
    QString target = fEdit.text();
    if((fTextEdit != nullptr) && (target != ""))
    {
        QString text = fTextEdit -> toPlainText();
        QTextCursor cursor = fTextEdit -> textCursor();
        int index = -1;
        if(forwardRatio.isChecked())
        {
            index = text.indexOf(target, cursor.position(), fCheck.isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
            if(index >= 0)
            {
                cursor.setPosition(index + target.length());
                cursor.setPosition(index + target.length(), QTextCursor::KeepAnchor);
                fTextEdit -> setTextCursor(cursor);
            }
        }
        if(backRatio.isChecked())
        {
            index = text.lastIndexOf(target, cursor.position() - text.length() - 1, fCheck.isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
            if(index >= 0)
            {
                cursor.setPosition(index + target.length());
                cursor.setPosition(index, QTextCursor::KeepAnchor);
                fTextEdit -> setTextCursor(cursor);
            }
        }
        if(index < 0)
        {
            QMessageBox::information(this, "查找", "找不到 \"" + target + "\"", QMessageBox::Ok);
        }
    }
}

void findDialog::onCancel()
{
    close();
}
