#include "replacedialog.h"

replaceDialog::replaceDialog(QWidget* parent, QPlainTextEdit* pText) : findDialog (parent, pText)
{
    replaceLabel.setText("替换为(&P)");
    replaceButton.setText("替换(&R)");
    replaceAllButton.setText("全部替换(&A)");

    fLayout.removeWidget(&fCheck);
    fLayout.removeWidget(&fRadioGroup);
    fLayout.removeWidget(&cancelButton);

    fLayout.addWidget(&replaceLabel, 1, 0);
    fLayout.addWidget(&replaceEdit, 1, 1);
    fLayout.addWidget(&replaceButton, 1, 2);

    fLayout.addWidget(&fCheck, 2, 0);
    fLayout.addWidget(&fRadioGroup, 2, 1);
    fLayout.addWidget(&replaceAllButton, 2, 2);

    fLayout.addWidget(&cancelButton, 3, 2);

    setWindowTitle("替换");

    connect(&replaceButton, SIGNAL(clicked()), this, SLOT(onReplace()));
    connect(&replaceAllButton, SIGNAL(clicked()), this, SLOT(onReplaceAll()));
}


void replaceDialog::onReplace()
{
    QString target = fEdit.text();
    QString to = replaceEdit.text();
    if((fTextEdit != nullptr) && (target != nullptr) && (to != nullptr))
    {
        QString select = fTextEdit -> textCursor().selectedText();
        if(select == target)
        {
            fTextEdit -> insertPlainText(to);
        }
        onFind();
    }
}

void replaceDialog::onReplaceAll()
{
    QString target = fEdit.text();
    QString to = replaceEdit.text();
    if((fTextEdit != nullptr) && (target != nullptr) && (to != nullptr))
    {
        QString text = fTextEdit -> toPlainText();
        text.replace(target, to, fCheck.isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
        fTextEdit -> clear();
        fTextEdit -> insertPlainText(text);
    }
}
