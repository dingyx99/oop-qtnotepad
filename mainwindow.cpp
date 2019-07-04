#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->toolBar_1->addAction(ui->fontComboBox);
    connect(ui->action_new,SIGNAL(clicked(bool)), this, SLOT(on_action_new_triggered(bool)));   //新建
    connect(ui->action_new,SIGNAL(clicked(bool)), this, SLOT(on_action_open_triggered()));   //打开
    connect(ui->action_new,SIGNAL(clicked(bool)), this, SLOT(on_action_save_triggered()));    //保存
    connect(ui->action_new,SIGNAL(clicked(bool)), this, SLOT(on_action_saveAs_triggered()));   //另存为
    connect(ui->action_new,SIGNAL(clicked(bool)), this, SLOT(on_action_print_triggered()));   //打印
    connect(ui->action_new,SIGNAL(clicked(bool)), this, SLOT(on_action_printView_triggered()));  //打印预览
    connect(ui->action_new,SIGNAL(clicked(bool)), this, SLOT(on_action_exit_triggered()));

    connect(ui->action_new,SIGNAL(clicked(bool)), this, SLOT(on_action_undo_triggered()));  //撤销
    connect(ui->action_new,SIGNAL(clicked(bool)), this, SLOT(on_action_redo_triggered()));   //重做
    connect(ui->action_new,SIGNAL(clicked(bool)), this, SLOT(on_action_copy_triggered()));   //复制
    connect(ui->action_new,SIGNAL(clicked(bool)), this, SLOT(on_action_cut_triggered()));     //剪切
    connect(ui->action_new,SIGNAL(clicked(bool)), this, SLOT(on_action_paste_triggered()));    //粘贴
    connect(ui->action_new,SIGNAL(clicked(bool)), this, SLOT(on_action_find_triggered()));   //查找
    connect(ui->action_new,SIGNAL(clicked(bool)), this, SLOT(on_action_replace_triggered));   //替换

    connect(ui->action_new,SIGNAL(clicked(bool)), this, SLOT(on_action_bold_triggered()));    //加粗
    connect(ui->action_new,SIGNAL(clicked(bool)), this, SLOT(on_action_italic_triggered()));    //倾斜
    connect(ui->action_new,SIGNAL(clicked(bool)), this, SLOT(on_action_underline_triggered()));    //下划线
    connect(ui->action_new,SIGNAL(clicked(bool)), this, SLOT(on_action_color_triggered()));    //颜色
    connect(ui->action_new,SIGNAL(clicked(bool)), this, SLOT(on_action_leftAlign_triggered()));  //左对齐
    connect(ui->action_new,SIGNAL(clicked(bool)), this, SLOT(on_action_center_triggered()));  //居中
    connect(ui->action_new,SIGNAL(clicked(bool)), this, SLOT(on_action_right_triggered()));  //右对齐
    connect(ui->action_new,SIGNAL(clicked(bool)), this, SLOT(on_action_justifyAlign_triggered()));  //中心对齐

    connect(ui->action_new,SIGNAL(clicked(bool)), this, SLOT(on_action_drawPoint_triggered()));  //绘制点
    connect(ui->action_new,SIGNAL(clicked(bool)), this, SLOT(on_action_drawLine_triggered()));  //绘制线
    connect(ui->action_new,SIGNAL(clicked(bool)), this, SLOT(on_action_drawCircle_triggered()));  //绘制圆

    connect(ui->action_new,SIGNAL(clicked(bool)), this, SLOT(on_action_about_triggered()));  //关于
    connect(ui->action_new,SIGNAL(clicked(bool)), this, SLOT(on_action_about3rdParty_triggered()));  //第三方声明

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

void MainWindow::on_action_new_triggered()
{
    qDebug() << "success1";
    box *newfile = new box;     //新建窗口
    ui->mdiArea->addSubWindow(newfile);     //将窗口放在容器内
    newfile->creatFile();     //设置新建窗口的名称，依次增加
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

    newfile->setFilePath(filepath);    //传入打开的文件路径
    newfile->show();
}

void MainWindow::on_action_save_triggered()
{
    box * newfile = activeSubwin();
    if(newfile==nullptr){
        QMessageBox::warning(this,"提示","没有可保存的文档");
        return;
    }

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
     if(newfile==nullptr){
         QMessageBox::warning(this, "提示", "没有可保存的文档");
         return;
     }
     newfile->saveFileAs();
}

void MainWindow::on_action_print_triggered()
{
    box * newfile = activeSubwin();
    if(newfile==nullptr){
        QMessageBox::warning(this,"提示","没有可打印的文档");
        return;
    }
     newfile->printFile();
}

void MainWindow::on_action_printView_triggered()
{
    box * newfile = activeSubwin();
    if(newfile==nullptr){
        QMessageBox::warning(this,"提示","没有可打印的文档");
        return;
    }
    newfile->printFileView();
}

void MainWindow::on_action_exit_triggered()
{

}

void MainWindow::on_action_undo_triggered()
{

}

void MainWindow::on_action_redo_triggered()
{

}

void MainWindow::on_action_copy_triggered()
{

}

void MainWindow::on_action_cut_triggered()
{

}

void MainWindow::on_action_paste_triggered()
{

}

void MainWindow::on_action_find_triggered()
{

}

void MainWindow::on_action_replace_triggered()
{

}

void MainWindow::on_action_bold_triggered()
{

}

void MainWindow::on_action_italic_triggered()
{

}

void MainWindow::on_action_underline_triggered()
{

}

void MainWindow::on_action_color_triggered()
{

}

void MainWindow::on_action_leftAlign_triggered()
{

}

void MainWindow::on_action_center_triggered()
{

}


void MainWindow::on_action_justifyAlign_triggered()
{

}

void MainWindow::on_action_rightAlign_triggered()
{

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

}

void MainWindow::on_action_about3rdParty_triggered()
{

}
