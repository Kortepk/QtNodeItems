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
        ConnectionButton *button = new ConnectionButton();
        button->setText(QString::number(i));
        connect(button, &ConnectionButton::pressed, this, &NodeItem::doteClicked);
        conBut.append(button);
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

QVector<ConnectionButton *> NodeItem::getConnectionButton()
{
    return conBut;
}

void NodeItem::moveConButtons(QPointF newPos)
{
    QRectF rect = mainTable->boundingRect();

    qreal w = rect.width();
    qreal h = rect.height();
    qreal diam = conBut[0]->boundingRect().width();
    qDebug() << diam;
    qreal m = 6; // margin

    conBut[0]->setPos(newPos.x() + w/2 - diam/2, newPos.y() - diam - m);
    conBut[1]->setPos(newPos.x() + w + m, newPos.y() + h/2 - diam/2);
    conBut[2]->setPos(newPos.x() + w/2 - diam/2, newPos.y() + h + m);
    conBut[3]->setPos(newPos.x() - diam - m, newPos.y() + h/2 - diam/2);

}

void NodeItem::doteClicked()
{
    qDebug() << __PRETTY_FUNCTION__;

    ConnectionButton* but = qobject_cast<ConnectionButton*>(sender());
    if(!but)
        return;

    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;

    mimeData->setText(NodeId);
    QByteArray byteArray = but->text().toUtf8();
    mimeData->setData("application/node-data", byteArray);

    drag->setMimeData(mimeData);

    // Start drag and drop
    Qt::DropAction dropAction = drag->exec(Qt::LinkAction);

    if (dropAction == Qt::LinkAction)
    {
        ; // Success
    }
}
