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
    for(int i = 0; i < BUTTON_COUNT; i ++){
        ConnectionButton *button = new ConnectionButton(i);
        button->setText(QString::number(i));
        connect(button, &ConnectionButton::pressed, this, &NodeItem::doteClicked);
        connect(button, &ConnectionButton::dropNodeHere, this, &NodeItem::bindNodeHandler);
        conBut.append(button);
    }
    conLine.resize(conBut.count());
    beginPoint.resize(conBut.count());
    conNode.resize(conBut.count());

    connect(mainTable, &NodeTable::newPosition, this, &NodeItem::moveConButtons);
    connect(mainTable, &NodeTable::destroyed, this, &NodeItem::tableDestroyedHandler);
}

void NodeItem::tableDestroyedHandler()
{
    for(int i = 0; i < BUTTON_COUNT; i++){
        if(conLine[i] != nullptr){
            conNode[i]->removeLink(conLine[i]);
            delete conLine[i];
        }
        delete conBut[i];
    }
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

QString NodeItem::getNodeId()
{
    return NodeId;
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
    qreal rad = diam/2;
    qreal m = 6; // margin

    QPointF point[BUTTON_COUNT] = {
        {newPos.x() + w/2 - rad, newPos.y() - diam - m},
        {newPos.x() + w + m, newPos.y() + h/2 - rad},
        {newPos.x() + w/2 - rad, newPos.y() + h + m},
        {newPos.x() - diam - m, newPos.y() + h/2 - rad}
    };

    QPointF center(rad, rad);

    for(int i = 0; i < BUTTON_COUNT; i++){
        conBut[i]->setPos(point[i]);

        if(conLine[i] != nullptr){
            QLineF ln = conLine[i]->line();
            if(beginPoint[i])
                ln.setP1(point[i] + center);
            else
                ln.setP2(point[i] + center);
            conLine[i]->setLine(ln);
        }
    }
}

QPointF NodeItem::getDragStartPos()
{
    return conButtonStartPos;
}

void NodeItem::doteClicked(int butIndex)
{
    ConnectionButton* but = qobject_cast<ConnectionButton*>(sender());
    if(!but)
        return;

    conButtonStartPos = but->pos() + but->boundingRect().center();

    if(butIndex < 0)
        return;

    // if the line is already connected
    if(conLine[butIndex]){
        conNode[butIndex]->removeLink(conLine[butIndex]);
        delete conLine[butIndex];
        conLine[butIndex] = nullptr;
    }

    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;

    mimeData->setText(NodeId);

    QByteArray byteArray;
    byteArray.setNum(butIndex);
    mimeData->setData("application/node-data", byteArray);

    drag->setMimeData(mimeData);

    // Start drag and drop
    Qt::DropAction dropAction = drag->exec(Qt::LinkAction);

    if (dropAction == Qt::LinkAction)
    {
        ; // Success
    }
}

void NodeItem::bindNodeHandler(int index, QPair<QString, int> sender)
{
    emit createLinkNode({NodeId, index}, sender);
}

void NodeItem::removeLink(QGraphicsLineItem *line)
{
    for(int i = 0; i < BUTTON_COUNT; i++){
        if(!conNode[i])
            continue;

        if(conLine[i] == line){
            conLine[i] = nullptr;
            conNode[i] = nullptr;
        }
    }
}

void NodeItem::addConectionLine(QGraphicsLineItem *newLine, int butIndex, bool isBegin, NodeItem *otherNode)
{
    // Joining yourself
    if(otherNode->getNodeId() == NodeId){
        if(isBegin)
            delete newLine;
        return;
    }

    // if the line is already connected
    if(conLine[butIndex]){
        conNode[butIndex]->removeLink(conLine[butIndex]);
        delete conLine[butIndex];
        qDebug() << __PRETTY_FUNCTION__ << "delete line";
        conLine[butIndex] = nullptr;
        conNode[butIndex] = nullptr;
    }

    conLine[butIndex] = newLine;
    beginPoint[butIndex] = isBegin;
    conNode[butIndex] = otherNode;

    // Update position
    moveConButtons(mainTable->pos());
}

