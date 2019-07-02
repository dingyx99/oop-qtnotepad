#ifndef BOX_H
#define BOX_H

#include <QWidget>
#include<QTextEdit>

namespace Ui {
class box;
}

class box : public QTextEdit
{
    Q_OBJECT

public:
    explicit box(QWidget *parent = nullptr);
    ~box();
    void creatFile();

private:
    Ui::box *ui;

};

#endif // BOX_H
