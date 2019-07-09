#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->toolBar_1->addWidget(ui->fontComboBox);
    ui->toolBar_1->addWidget(ui->comboBox_fontSize);

    ui->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(ui->mdiArea);

//    QStringList list = (QStringList() << "1" << "2" << "3");
//    ui->comboBox_fontSize->addItems(list);

    //让对齐类按钮互斥
    QActionGroup * alignmentGroup = new QActionGroup(this);
    alignmentGroup->addAction(ui->action_leftAlign);
    alignmentGroup->addAction(ui->action_center);
    alignmentGroup->addAction(ui->action_rightAlign);
    alignmentGroup->addAction(ui->action_justifyAlign);
    ui->action_leftAlign->setChecked(true);

    connect(ui->action_new,SIGNAL(toggled()), this, SLOT(on_action_new_triggered(bool)));   //新建
    connect(ui->action_open,SIGNAL(toggled()), this, SLOT(on_action_open_triggered()));   //打开
    connect(ui->action_save,SIGNAL(toggled()), this, SLOT(on_action_save_triggered()));    //保存
    connect(ui->action_saveAs,SIGNAL(toggled()), this, SLOT(on_action_saveAs_triggered()));   //另存为
    connect(ui->action_print,SIGNAL(toggled()), this, SLOT(on_action_print_triggered()));   //打印
    connect(ui->action_printView,SIGNAL(toggled()), this, SLOT(on_action_printView_triggered()));  //打印预览
    connect(ui->action_exit,SIGNAL(toggled()), this, SLOT(on_action_exit_triggered()));   //退出

    connect(ui->action_undo,SIGNAL(toggled()), this, SLOT(on_action_undo_triggered()));  //撤销
    connect(ui->action_redo,SIGNAL(toggled()), this, SLOT(on_action_copy_triggered()));   //复制
    connect(ui->action_cut,SIGNAL(toggled()), this, SLOT(on_action_cut_triggered()));     //剪切
    connect(ui->action_paste,SIGNAL(toggled()), this, SLOT(on_action_paste_triggered()));    //粘贴
    connect(ui->action_find,SIGNAL(toggled()), this, SLOT(on_action_find_triggered()));   //查找
    connect(ui->action_replace,SIGNAL(toggled()), this, SLOT(on_action_replace_triggered));   //替换

    connect(ui->action_bold,SIGNAL(toggled()), this, SLOT(on_action_bold_triggered()));    //加粗
    connect(ui->action_italic,SIGNAL(toggled()), this, SLOT(on_action_italic_triggered()));    //倾斜
    connect(ui->action_underline,SIGNAL(toggled()), this, SLOT(on_action_underline_triggered()));    //下划线
    connect(ui->action_color,SIGNAL(toggled()), this, SLOT(on_action_color_triggered()));    //颜色
    connect(ui->action_leftAlign,SIGNAL(toggled()), this, SLOT(setAlign(1)));  //左对齐
    connect(ui->action_center,SIGNAL(toggled()), this, SLOT(setAlign(2)));  //居中
    connect(ui->action_rightAlign,SIGNAL(toggled()), this, SLOT(setAlign(3)));  //右对齐
    connect(ui->action_justifyAlign,SIGNAL(toggled()), this, SLOT(setAlign(4)));  //中心对齐

    connect(ui->action_drawPoint,SIGNAL(toggled()), this, SLOT(on_action_drawPoint_triggered()));  //绘制点
    connect(ui->action_drawLine,SIGNAL(toggled()), this, SLOT(on_action_drawLine_triggered()));  //绘制线
    connect(ui->action_drawCircle,SIGNAL(toggled()), this, SLOT(on_action_drawCircle_triggered()));  //绘制圆

    connect(ui->action_about,SIGNAL(toggled()), this, SLOT(on_action_about_triggered()));  //关于
    connect(ui->action_about3rdParty, SIGNAL(triggered()), this, SLOT(on_action_about_qt_triggered()));  //第三方声明

    connect(ui->fontComboBox,SIGNAL(activated(QString)),this, SLOT(on_fontComboBox_currentFontChanged(QString))); //字体
    connect(ui->comboBox_fontSize,SIGNAL(activated(QString)),this, SLOT(on_comboBox_fontSize_activated(QString)));

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
    box *currentFile = (box *)wid;
    if(currentFile==nullptr){
        return nullptr;
    }
    return currentFile;
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
        ui->comboBox_fontSize->setDisabled(true);
        ui->fontComboBox->setDisabled(true);
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
    ui->comboBox_fontSize->setEnabled(true);
    ui->fontComboBox->setEnabled(true);
}

void MainWindow::on_action_new_triggered()
{
    box *currentFile = new box;     //新建窗口
    ui->mdiArea->addSubWindow(currentFile);     //将窗口放在容器内
    currentFile->creatFile();     //设置新建窗口的名称，依次增加
    setEnable();
    currentFile->show();
}

void MainWindow::on_action_open_triggered()
{
    QString filepath = QFileDialog::getOpenFileName(this, QString("open a file"),
                                 QString("/"), "HTML 文档 (*.htm *.html);;所有文件 (*.*)");  //获取文件路径
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

    box *currentFile = new box;      //新建窗口并将文档写入
    currentFile->setText(text_utf);
    ui->mdiArea->addSubWindow(currentFile);     //将窗口放在容器内
    currentFile->setWindowTitle(filename);     //设置"窗口名"为当前打开的"文件名"

    setEnable();
    currentFile->setFilePath(filepath);    //传入打开的文件路径
    currentFile->show();
}

void MainWindow::on_action_save_triggered()
{
    box * currentFile = activeSubwin();
     if(currentFile->getFilePath()!=""){
         currentFile->saveFile();     //若文件有路径，调用保存
     }
     else {
         currentFile->saveFileAs();   //若文件无路径，调用另存为
     }
}

void MainWindow::on_action_saveAs_triggered()
{
     box *currentFile = activeSubwin();
     currentFile->saveFileAs();
}

void MainWindow::on_action_print_triggered()
{
    box * currentFile = activeSubwin();
     currentFile->printFile();
}

void MainWindow::on_action_printView_triggered()
{
    box * currentFile = activeSubwin();
    currentFile->printFileView();
}

void MainWindow::on_action_exit_triggered()
{
    exit(0);
}

void MainWindow::on_action_undo_triggered()
{
    box * currentFile = activeSubwin();
    currentFile -> undo();
}

void MainWindow::on_action_redo_triggered()
{
    box * currentFile = activeSubwin();
    currentFile -> redo();
}

void MainWindow::on_action_copy_triggered()
{
    box * currentFile = activeSubwin();
    currentFile->copyText();
}

void MainWindow::on_action_cut_triggered()
{
    box * currentFile = activeSubwin();
    currentFile->cutText();
}

void MainWindow::on_action_paste_triggered()
{
    box * currentFile = activeSubwin();
    currentFile->pasteText();
}

void MainWindow::on_action_find_triggered()
{

}

void MainWindow::on_action_replace_triggered()
{

}

void MainWindow::on_action_bold_triggered()
{
    box * currentFile = activeSubwin();
    ui->action_bold->isChecked() ? currentFile->setBold() : currentFile->setPlain(1);
}

void MainWindow::on_action_italic_triggered()
{
    box * currentFile = activeSubwin();
    ui->action_italic->isChecked() ? currentFile->setItalic() : currentFile->setPlain(2);
}

void MainWindow::on_action_underline_triggered()
{
    box * currentFile = activeSubwin();
    ui->action_underline->isChecked() ? currentFile->setUnderline() : currentFile->setPlain(3);
}

void MainWindow::on_action_color_triggered()
{
    box * currentFile = activeSubwin();
    currentFile->setColor();
}

void MainWindow::on_action_leftAlign_triggered()
{
    box * currentFile = activeSubwin();
    currentFile->setAlignment(Qt::AlignLeft);
}

void MainWindow::on_action_center_triggered()
{
    box * currentFile = activeSubwin();
    currentFile->setAlignment(Qt::AlignCenter);
}


void MainWindow::on_action_justifyAlign_triggered()
{
    box * currentFile = activeSubwin();
    currentFile->setAlignment(Qt::AlignJustify);
}

void MainWindow::on_action_rightAlign_triggered()
{
    box * currentFile = activeSubwin();
    currentFile->setAlignment(Qt::AlignRight);
}

void MainWindow::on_action_drawPoint_triggered()
{
    box * currentFile = activeSubwin();
    currentFile->append("<img src=\":/new/images/svg/dot.svg\"></img>");
}
void MainWindow::on_action_drawLine_triggered()
{
    box * currentFile = activeSubwin();
    currentFile->append("<img src=\":/new/images/svg/line.svg\"></img>");
}

void MainWindow::on_action_drawCircle_triggered()
{
    box * currentFile = activeSubwin();
    currentFile->append("<img src=\":/new/images/svg/circle.svg\"></img>");
}

void MainWindow::on_action_about_triggered()
{
    aboutDialog().exec();
}

void MainWindow::on_action_about_qt_triggered()
{
    QMessageBox::aboutQt(nullptr, "关于Qt");
}

void MainWindow::on_fontComboBox_currentFontChanged(QString fontFamily)
{
    box * currentFile = activeSubwin();
    currentFile->setFont(fontFamily);
}

void MainWindow::on_comboBox_fontSize_activated(QString fontsize)
{
    box * currentFile = activeSubwin();
    currentFile->setSize(fontsize.toDouble());
}
