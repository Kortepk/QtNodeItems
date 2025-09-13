#include "nodeitem.h"
#include "qpainter.h"

NodeItem::NodeItem(QGraphicsItem *parent)
    : QGraphicsRectItem(parent)
{
    generalInit();
}

NodeItem::NodeItem(const QRectF &rect, QGraphicsItem *parent)
    : QGraphicsRectItem(rect, parent)
{
    generalInit();
}

NodeItem::NodeItem(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent)
    : QGraphicsRectItem(x, y, width, height, parent)
{
    generalInit();
}

void NodeItem::generalInit()
{
    setFlag(ItemIsMovable, true);
    setPen(QPen(Qt::black, 2)); // Border

    nodeFont.setFamily("Arial");
    nodeFont.setPixelSize(10);
}

void NodeItem::setNodeId(QString newNodeId)
{
    NodeId = newNodeId;
}

QString NodeItem::nodeId()
{
    return NodeId;
}

void NodeItem::setText(QString newText)
{
    TitleText = newText;
}

QString NodeItem::text()
{
    return TitleText;
}

void NodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsRectItem::paint(painter, option, widget);

    painter->setFont(nodeFont);

    painter->drawText(QPointF(5, 10), TitleText);
}
