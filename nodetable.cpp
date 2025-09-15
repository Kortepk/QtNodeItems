#include "nodetable.h"
#include "qpainter.h"

NodeTable::NodeTable()
    : QGraphicsObject()
{
    rectItem.setRect(0, 0, 100, 100);
    generalInit();
}

NodeTable::NodeTable(qreal x, qreal y, qreal width, qreal height)
{
    rectItem.setRect(x, y, width, height);
    generalInit();
}

void NodeTable::generalInit()
{
    setFlag(ItemIsMovable, true);

    nodeFont.setFamily("Arial");
    nodeFont.setPixelSize(10);
}

void NodeTable::setNodeId(QString newNodeId)
{
    NodeId = newNodeId;
}

QString NodeTable::nodeId()
{
    return NodeId;
}

void NodeTable::setText(QString newText)
{
    TitleText = newText;
}

QString NodeTable::text()
{
    return TitleText;
}

void NodeTable::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black, 2)); // Border
    painter->setBrush(mainBrush);

    painter->drawRect(rectItem);

    painter->setFont(nodeFont);
    painter->drawText(QPointF(5, 10), TitleText);
}


void NodeTable::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit newPosition(pos());

    QGraphicsObject::mouseMoveEvent(event);
}

void NodeTable::setBrush(QBrush newBrush)
{
    mainBrush = newBrush;
}

QRectF NodeTable::boundingRect() const
{
    return rectItem;
}

bool NodeTable::event(QEvent *ev)
{
    return QObject::event(ev);
}

