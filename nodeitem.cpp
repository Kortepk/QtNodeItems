#include "nodeitem.h"

NodeItem::NodeItem(QWidget *parent)
    : QWidget{parent}
{
    mainTable = new NodeTable();
    generalInit();
}

NodeItem::NodeItem(qreal x, qreal y, qreal width, qreal height, QWidget *parent)
    : QWidget{parent}
{
    mainTable = new NodeTable(x, y, width, height);
    generalInit();
}

void NodeItem::generalInit()
{
    for(int i = 0; i < 4; i ++){
        QPushButton *rb = new QPushButton();
        rb->setMaximumSize(12, 12);
        rb->setStyleSheet("background-color: transparent;"
                          "border: 1px solid black;"
                          "border-radius: 6px;");
        conBut.append(rb);
    }

    connect(mainTable, &NodeTable::newPosition, this, &NodeItem::moveConButtons);
}

void NodeItem::setText(QString newText)
{
    TitleText = newText;
    mainTable->setText(newText);

}

void NodeItem::setNodeId(QString newNodeId)
{
    NodeId = newNodeId;
    mainTable->setNodeId(newNodeId);
}

void NodeItem::setBrush(QBrush newBrush)
{
    tableBrush = newBrush;
    mainTable->setBrush(newBrush);
}

NodeTable *NodeItem::getTable()
{
    return mainTable;
}

QVector<QPushButton *> NodeItem::getConnectionButton()
{
    return conBut;
}

void NodeItem::moveConButtons(QPointF newPos)
{
    QRectF rect = mainTable->boundingRect();

    qreal w = rect.width();
    qreal h = rect.height();
    qreal diam = conBut[0]->size().width();
    qDebug() << diam;
    qreal m = 6; // margin

    conBut[0]->move(newPos.x() + w/2 - diam/2, newPos.y() - diam - m);
    conBut[1]->move(newPos.x() + w + m, newPos.y() + h/2 - diam/2);
    conBut[2]->move(newPos.x() + w/2 - diam/2, newPos.y() + h + m);
    conBut[3]->move(newPos.x() - diam - m, newPos.y() + h/2 - diam/2);

}
