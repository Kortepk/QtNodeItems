#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addNode_pb_clicked()
{
    qDebug() << "Title now: " + ui->nodeName_le->text();
    qDebug() << "Color now: " + colorNow.name();
}


void MainWindow::on_nodeColor_pb_clicked()
{
    colorNow = QColorDialog::getColor(Qt::white);
    if (colorNow.isValid()) {
        QString colorStr = QString("background-color: %1;border-radius: 4px;").arg(colorNow.name());
        ui->colorSquare->setStyleSheet(colorStr);
    }
}

