#include "box.h"
#include "ui_box.h"



box::box(QWidget *parent) :
    QTextEdit(parent),
    ui(new Ui::box)
{
    ui->setupUi(this);
    //connect(this->close(),SIGNAL(clicked(bool)),this,SLOT(box::test()));
    //"查找"窗口
    findDlg = new QDialog(this);
    findDlg->setWindowTitle("查找");
    findLineEdit = new QLineEdit(findDlg);
    QPushButton *findBtn = new QPushButton("上一个", findDlg);
    QVBoxLayout *layout = new QVBoxLayout(findDlg);
    layout->addWidget(findLineEdit);
    layout->addWidget(findBtn);
    connect(findBtn, SIGNAL(clicked()), this, SLOT(on_action_findDlg_triggered()));
}

box::~box()
{
    delete ui;
}

void box::setFilePath(QString filepath){
    filePath = filepath;
}
QString box::getFilePath(){
    return filePath;
}
void box::setFileContent(QString filecontent){
    fileContent = filecontent;
}
QString box::getFileContent(){
    return fileContent;
}

void box::creatFile()
{
    static int number = 1;
    QString str = QString("文档%1").arg(number);
    number++;
    this->setWindowTitle(str);
    filePath = "";
}

void box::saveFileAs()
{
    QString filepath = QFileDialog::getSaveFileName(this, "另存为",
                                   "未命名文档", "HTML 文档 (*.htm *.html);;所有文件 (*.*)");
    QFile file;
    file.setFileName(filepath);
    if(!file.open(QIODevice::WriteOnly)){     //打开文档
        QMessageBox::warning(this, "waring", "文档未保存");
    }
    QTextStream out(&file);
    QString str = this->document()->toHtml();  //提取文档内容
    out << str;     //把文档内容写入新建文档
    if(filepath!="")
    {
        QMessageBox::information(this, "提示", "文档保存成功");
        document()->setModified(false);
    }
    else {
        document()->setModified(true);
    }
    file.close();    //关闭文档
}

void box::saveFile()
{
    QFile file(filePath);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    QString str = this->document()->toHtml();
    out << str;
    QMessageBox::information(this, "提示", "文档保存成功");
    document()->setModified(false);
    file.close();
}

void box::printFile()
{
    QPrinter printer;
    QPrintDialog dialog(&printer, this);
    if(this->textCursor().hasSelection()){
        dialog.addEnabledOption(QAbstractPrintDialog::PrintSelection);
    }
    if(dialog.exec()==QDialog::Accepted){
        this->print(&printer);
    }
}

void box::printFileView()
{
    QPrinter printer;
    QPrintPreviewDialog viewDlg(&printer, this);
    connect(&viewDlg, &QPrintPreviewDialog::paintRequested, [=](QPrinter *printer) {
            this->print(printer);});
    viewDlg.exec();
}

void box::copyText()
{
    QString text = textCursor().selectedText();   //仅文本
    //QTextDocumentFragment text = textCursor().selection();   //文本+格式
    setFileContent(text);
}

void box::cutText()
{
    QString text = textCursor().selectedText();
    setFileContent(text);
    //textCursor().selectedText().clear();
    //this->textCursor().selectedText().clear();
    this->textCursor().insertText("");
}

void box::pasteText()
{
    this->textCursor().insertText(getFileContent());
}

void box::setBold()
{
    QTextCharFormat fmt;
    fmt.setFontWeight(QFont::Bold);
    mergeFormat(fmt);    //使格式作用于选区内的字符
}

void box::setItalic()
{
    QTextCharFormat fmt;
    fmt.setFontItalic(true);
    mergeFormat(fmt);
}

void box::setUnderline()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(true);
    mergeFormat(fmt);
}

void box::setPlain(int status)
{
    QTextCharFormat fmt;
    switch (status) {
        case 1 :
        fmt.setFontWeight(QFont::Normal);
        break;
    case 2 :
        fmt.setFontItalic(false);
        break;
    case 3 :
        fmt.setFontUnderline(false);
        break;
    default:
        break;
    }
    mergeFormat(fmt);
}

void box::setColor()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "Select Color", QColorDialog::DontUseNativeDialog);
        if(color.isValid())
        {
            this->setTextColor(color);
        }
    //QTextCharFormat fmt;
}

void box::setFont(QString fontFamily)
{
    QTextCharFormat fmt;
    //QString fontName = font.styleName();
    //QString fontName = font.family();
    fmt.setFontFamily(fontFamily);
    mergeFormat(fmt);
}

void box::setSize(double size)
{
    QTextCharFormat fmt;
    fmt.setFontPointSize(size);
    mergeFormat(fmt);
}

//设置光标的选区，使格式作用于选区内的字符，若没有选区则作用于光标所在处的字符
void box::mergeFormat(QTextCharFormat format)
{
    QTextCursor cursor = this->textCursor();
    if (!cursor.hasSelection())
       cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
    this->mergeCurrentCharFormat(format);
}
//调用QTextCursor的mergeCharFormat()函数把参数format所表示的格式
//应用到光标所在处的字符上
//调用QTextEdit的mergeCurrentCharFormat()函数把格式应用到选区内的所有字符上

void box::closeEvent(QCloseEvent *event)
{
    if (!document()->isModified())
        return;
    QMessageBox::StandardButton button;
    button = QMessageBox::warning(this, tr("Myself Qt Word"),tr("文档已被修改,保存吗?")
                     ,QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

    if(button==QMessageBox::Save)
    {
        if(this->getFilePath()=="") {
            saveFileAs();
            event->ignore();    //保存后保留页面
        }
        else {
            saveFile();
            event->ignore();
        }
    }
    else if(button==QMessageBox::Cancel)
    {
        event->ignore(); // 忽略退出信号，程序继续进行
    }
    else if(button==QMessageBox::Discard)
    {
        event->accept();
    }
}

void box::on_action_findDlg_triggered()
{
    box * current = this;
    QString str = findLineEdit->text();
    bool isFind = current->find(str, QTextDocument::FindBackward);   //从后向前查找

    QPalette palette = current->palette();    //高亮显示
    palette.setColor(QPalette::Highlight,palette.color(QPalette::Active,QPalette::Highlight));
    current->setPalette(palette);

    if(isFind==false)
    {
        QMessageBox::warning(this, "提示", "未找到");
    }
}


QDialog* box::getFindDlg()
{
    return findDlg;
}

