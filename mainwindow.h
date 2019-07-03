#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include <QDebug>
#include <box.h>
#include <QFileDialog>
#include <QFile>
#include <QTextCodec>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_action_new_triggered();


    void on_action_open_triggered();

    void on_action_save_triggered();

    void on_action_saveAs_triggered();

    void on_action_print_triggered();

    void on_action_printView_triggered();

    void on_action_exit_triggered();

    void on_action_undo_triggered();

    void on_action_redo_triggered();

    void on_action_copy_triggered();

    void on_action_cut_triggered();

    void on_action_paste_triggered();

    void on_action_find_triggered();

    void on_action_replace_triggered();

    void on_action_bold_triggered();

    void on_action_italic_triggered();

    void on_action_underline_triggered();

    void on_action_color_triggered();

    void on_action_leftAlign_triggered();

    void on_action_center_triggered();

    void on_action_drawPoint_triggered();

    void on_action_justifyAlign_triggered();

    void on_action_rightAlign_triggered();

    void on_action_drawLine_triggered();

    void on_action_drawCircle_triggered();

    void on_action_about_triggered();

    void on_action_about3rdParty_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
