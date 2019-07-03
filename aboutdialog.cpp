#include "aboutdialog.h"

aboutDialog::aboutDialog(QWidget* parent)
                        :QDialog(parent, Qt::WindowCloseButtonHint), logoLabel(this), infoText(this), closeButton(this)
{
    QPixmap pm(":/new/images/team-1.png");
    pm = pm.scaled(120, 120, Qt::KeepAspectRatio);
    logoLabel.setPixmap(pm);
    logoLabel.move(20, 20);
    logoLabel.resize(120, 120);

    QPalette p = infoText.palette();
    p.setColor(QPalette::Active, QPalette::Base, palette().color(QPalette::Active, QPalette::Background));
    p.setColor(QPalette::Inactive, QPalette::Base, palette().color(QPalette::Inactive, QPalette::Background));
    infoText.setPalette(p);
    infoText.move(200, 30);
    infoText.resize(180, 200);
    infoText.setFrameStyle(QPlainTextEdit::NoFrame);
    infoText.setReadOnly(true);
    infoText.insertPlainText("基于Qt的文档编辑器\n\n作者: 陈虹坤 丁宇笑\n\nVersion: 1.0.0\n\n项目图标来自Office-Fabric-UI\n\n©Copyright 2019 Microsoft Corporation, All rights Reversed.");

    closeButton.setText("关闭");
    closeButton.move(273, 220);
    closeButton.resize(100, 30);

    setWindowTitle("关于本软件");
    setFixedSize(395, 250);
    connect(&closeButton, SIGNAL(clicked()), this, SLOT(onClose()));
}

void aboutDialog::onClose()
{
    close();
}
