#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->toolBar_1->addWidget(ui->fontComboBox);
    ui->toolBar_1->addWidget(ui->comboBox_fontSize);
    connect(ui->action_new,SIGNAL(clicked(bool)), this, SLOT(on_action_new_triggered(bool)));   //新建
    connect(ui->action_open,SIGNAL(clicked(bool)), this, SLOT(on_action_open_triggered()));   //打开
    connect(ui->action_save,SIGNAL(clicked(bool)), this, SLOT(on_action_save_triggered()));    //保存
    connect(ui->action_saveAs,SIGNAL(clicked(bool)), this, SLOT(on_action_saveAs_triggered()));   //另存为
    connect(ui->action_print,SIGNAL(clicked(bool)), this, SLOT(on_action_print_triggered()));   //打印
    connect(ui->action_printView,SIGNAL(clicked(bool)), this, SLOT(on_action_printView_triggered()));  //打印预览
    connect(ui->action_exit,SIGNAL(clicked(bool)), this, SLOT(on_action_exit_triggered()));   //退出

    connect(ui->action_undo,SIGNAL(clicked(bool)), this, SLOT(on_action_undo_triggered()));  //撤销
    connect(ui->action_redo,SIGNAL(clicked(bool)), this, SLOT(on_action_redo_triggered()));   //重做
    connect(ui->action_copy,SIGNAL(clicked(bool)), this, SLOT(on_action_copy_triggered()));   //复制
    connect(ui->action_cut,SIGNAL(clicked(bool)), this, SLOT(on_action_cut_triggered()));     //剪切
    connect(ui->action_paste,SIGNAL(clicked(bool)), this, SLOT(on_action_paste_triggered()));    //粘贴
    connect(ui->action_find,SIGNAL(clicked(bool)), this, SLOT(on_action_find_triggered()));   //查找
    connect(ui->action_replace,SIGNAL(clicked(bool)), this, SLOT(on_action_replace_triggered));   //替换

    connect(ui->action_bold,SIGNAL(checked()), this, SLOT(on_action_bold_triggered()));    //加粗
    connect(ui->action_italic,SIGNAL(clicked(bool)), this, SLOT(on_action_italic_triggered()));    //倾斜
    connect(ui->action_underline,SIGNAL(clicked(bool)), this, SLOT(on_action_underline_triggered()));    //下划线
    connect(ui->action_color,SIGNAL(clicked(bool)), this, SLOT(on_action_color_triggered()));    //颜色
    connect(ui->action_leftAlign,SIGNAL(clicked(bool)), this, SLOT(on_action_leftAlign_triggered()));  //左对齐
    connect(ui->action_center,SIGNAL(clicked(bool)), this, SLOT(on_action_center_triggered()));  //居中
    connect(ui->action_rightAlign,SIGNAL(clicked(bool)), this, SLOT(on_action_right_triggered()));  //右对齐
    connect(ui->action_justifyAlign,SIGNAL(clicked(bool)), this, SLOT(on_action_justifyAlign_triggered()));  //中心对齐

    connect(ui->action_drawPoint,SIGNAL(clicked(bool)), this, SLOT(on_action_drawPoint_triggered()));  //绘制点
    connect(ui->action_drawLine,SIGNAL(clicked(bool)), this, SLOT(on_action_drawLine_triggered()));  //绘制线
    connect(ui->action_drawCircle,SIGNAL(clicked(bool)), this, SLOT(on_action_drawCircle_triggered()));  //绘制圆

    connect(ui->action_about,SIGNAL(clicked(bool)), this, SLOT(on_action_about_triggered()));  //关于
    connect(ui->action_about3rdParty,SIGNAL(clicked(bool)), this, SLOT(aboutQt()));  //第三方声明

    setDisable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

box* MainWindow::activeSubwin(){     //定位激活窗口
    QMdiSubWindow *subWindow = ui->mdiArea->activeSubWindow();
    if(subWindow==nullptr){
        return nullptr;
    }
    QWidget *wid = subWindow->widget();
    if(wid==nullptr){
        return nullptr;
    }
    box *newfile = (box *)wid;
    if(newfile==nullptr){
        return nullptr;
    }
    return newfile;
}

void MainWindow::setDisable()
{
        ui->action_save->setDisabled(true);
        ui->action_saveAs->setDisabled(true);
        ui->action_print->setDisabled(true);
        ui->action_printView->setDisabled(true);
        ui->action_undo->setDisabled(true);
        ui->action_redo->setDisabled(true);
        ui->action_copy->setDisabled(true);
        ui->action_cut->setDisabled(true);
        ui->action_paste->setDisabled(true);
        ui->action_find->setDisabled(true);
        ui->action_replace->setDisabled(true);
        ui->action_bold->setDisabled(true);
        ui->action_italic->setDisabled(true);
        ui->action_underline->setDisabled(true);
        ui->action_color->setDisabled(true);
        ui->action_leftAlign->setDisabled(true);
        ui->action_center->setDisabled(true);
        ui->action_rightAlign->setDisabled(true);
        ui->action_justifyAlign->setDisabled(true);
        ui->action_drawPoint->setDisabled(true);
        ui->action_drawLine->setDisabled(true);
        ui->action_drawCircle->setDisabled(true);
}

void MainWindow::setEnable()
{
    ui->action_save->setEnabled(true);
    ui->action_saveAs->setEnabled(true);
    ui->action_print->setEnabled(true);
    ui->action_printView->setEnabled(true);
    ui->action_undo->setEnabled(true);
    ui->action_redo->setEnabled(true);
    ui->action_copy->setEnabled(true);
    ui->action_cut->setEnabled(true);
    ui->action_paste->setEnabled(true);
    ui->action_find->setEnabled(true);
    ui->action_replace->setEnabled(true);
    ui->action_bold->setEnabled(true);
    ui->action_italic->setEnabled(true);
    ui->action_underline->setEnabled(true);
    ui->action_color->setEnabled(true);
    ui->action_leftAlign->setEnabled(true);
    ui->action_center->setEnabled(true);
    ui->action_rightAlign->setEnabled(true);
    ui->action_justifyAlign->setEnabled(true);
    ui->action_drawPoint->setEnabled(true);
    ui->action_drawLine->setEnabled(true);
    ui->action_drawCircle->setEnabled(true);
}

void MainWindow::on_action_new_triggered()
{
    box *newfile = new box;     //新建窗口
    ui->mdiArea->addSubWindow(newfile);     //将窗口放在容器内
    newfile->creatFile();     //设置新建窗口的名称，依次增加
    setEnable();
    newfile->show();
}

void MainWindow::on_action_open_triggered()
{
    QString filepath = QFileDialog::getOpenFileName(this, QString("open a file"),
                                 QString("/"), "eXtensible Markup Language File(*.xml)");  //获取文件路径
    QFile file;
    file.setFileName(filepath);    //设置文件名称（路径）
    QFileInfo info(filepath);   //通过文档路径获取文档名称
    QString filename = info.fileName();

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(this,"提示","文件未打开");
        return;
    }   //以读和写的方式打开文件,若未打开任何文档，则不新建窗口

    QByteArray text = file.readAll();     //读文档：ALL
    QTextCodec *codec = QTextCodec::codecForName("GBK");    //将读取的文档内容编码格式转为GBK,能够显示中文
    QString text_utf = codec->toUnicode(text);

    box *newfile = new box;      //新建窗口并将文档写入
    newfile->setText(text_utf);
    ui->mdiArea->addSubWindow(newfile);     //将窗口放在容器内
    newfile->setWindowTitle(filename);     //设置"窗口名"为当前打开的"文件名"

    setEnable();
    newfile->setFilePath(filepath);    //传入打开的文件路径
    newfile->show();
}

void MainWindow::on_action_save_triggered()
{
    box * newfile = activeSubwin();
     if(newfile->getFilePath()!=""){
         newfile->saveFile();     //若文件有路径，调用保存
     }
     else {
         newfile->saveFileAs();   //若文件无路径，调用另存为
     }
}

void MainWindow::on_action_saveAs_triggered()
{
     box *newfile = activeSubwin();
     newfile->saveFileAs();
}

void MainWindow::on_action_print_triggered()
{
    box * newfile = activeSubwin();
     newfile->printFile();
}

void MainWindow::on_action_printView_triggered()
{
    box * newfile = activeSubwin();
    newfile->printFileView();
}

void MainWindow::on_action_exit_triggered()
{
    exit(0);
}

void MainWindow::on_action_undo_triggered()
{
    box * newfile = activeSubwin();
    newfile -> undo();
}

void MainWindow::on_action_redo_triggered()
{
    box * newfile = activeSubwin();
    newfile -> redo();
}

void MainWindow::on_action_copy_triggered()
{
    box * newfile = activeSubwin();
    newfile->copyText();
}

void MainWindow::on_action_cut_triggered()
{
    box * newfile = activeSubwin();
    newfile->cutText();
}

void MainWindow::on_action_paste_triggered()
{
    box * newfile = activeSubwin();
    newfile->pasteText();
}

void MainWindow::on_action_find_triggered()
{

}

void MainWindow::on_action_replace_triggered()
{

}

void MainWindow::on_action_bold_triggered()
{
    box * newfile = activeSubwin();
    if(ui->action_bold->isChecked())
    {
        newfile->setBold();
    }
    else {
        newfile->unsetBold();
    }

}

void MainWindow::on_action_italic_triggered()
{
    box * newfile = activeSubwin();
    newfile->setItalic();
}

void MainWindow::on_action_underline_triggered()
{
    box * newfile = activeSubwin();
    newfile->setUnderline();
}

void MainWindow::on_action_color_triggered()
{
    box * newfile = activeSubwin();
    newfile->setColor();
}

void MainWindow::on_action_leftAlign_triggered()
{
    box * newfile = activeSubwin();
    newfile->setAlignment(Qt::AlignLeft);
}

void MainWindow::on_action_center_triggered()
{
    box * newfile = activeSubwin();
    newfile->setAlignment(Qt::AlignCenter);
}


void MainWindow::on_action_justifyAlign_triggered()
{
    box * newfile = activeSubwin();
    newfile->setAlignment(Qt::AlignJustify);
}

void MainWindow::on_action_rightAlign_triggered()
{
    box * newfile = activeSubwin();
    newfile->setAlignment(Qt::AlignRight);
}

void MainWindow::on_action_drawPoint_triggered()
{

}
void MainWindow::on_action_drawLine_triggered()
{

}

void MainWindow::on_action_drawCircle_triggered()
{

}

void MainWindow::on_action_about_triggered()
{
    aboutDialog().exec();
}

void box::maybeSave()
{
    if (!document()->isModified())
        return;
    QMessageBox::StandardButton ret;
    ret = QMessageBox::warning(this, tr("Myself Qt Word"),tr("文档已被修改,保存吗?"),QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    if (ret == QMessageBox::Save)
    {
        saveFile();
        return;
    }
    else if (ret == QMessageBox::Cancel)
        return;
    return;
}


