#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

void MainWindow::on_action_new_triggered()
{
    //creatFile(ui);
    qDebug() << "success";
    box *newfile = new box;
    ui->mdiArea->addSubWindow(newfile);
    newfile->creatFile();
    newfile->show();
}

void MainWindow::on_action_open_triggered()
{

}

void MainWindow::on_action_save_triggered()
{

}

void MainWindow::on_action_saveAs_triggered()
{

}

void MainWindow::on_action_print_triggered()
{

}

void MainWindow::on_action_printView_triggered()
{

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
