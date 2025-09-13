#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    colorNow = QColor(Qt::white);

    mainScene = new QGraphicsScene(0, 0, 550-5, 300);
    ui->mainView_gv->setScene(mainScene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addNode_pb_clicked()
{
    QString nodeName = ui->nodeName_le->text();
    qDebug() << "Title now: " + nodeName;
    qDebug() << "Color now: " + colorNow.name();

    NodeItem *node = new NodeItem(0, 0, 100, 100);

    QString nodeId = nodeName;
    int i = 1;

    while(nodeMap.contains(nodeId)){
        nodeId = nodeName + QString("_%1").arg(i);
        i++;
    }

    // nodeId - unique value
    nodeMap[nodeId] = node;

    node->setText(nodeName);
    node->setBrush(QBrush(colorNow));

    mainScene->addItem(node);

    qDebug() << nodeMap;
}


void MainWindow::on_nodeColor_pb_clicked()
{
    colorNow = QColorDialog::getColor(colorNow);
    if (colorNow.isValid()) {
        QString colorStr = QString("background-color: %1;border-radius: 4px;").arg(colorNow.name());
        ui->colorSquare->setStyleSheet(colorStr);
    }
}

