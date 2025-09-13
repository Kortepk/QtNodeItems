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
    painter->save();

    painter->setFont(nodeFont);
    painter->drawText(QPointF(5, 10), TitleText);


    QBrush pointBrush(QColor(0, 0, 255, 128));

    painter->setPen(Qt::NoPen);
    painter->setBrush(pointBrush);

    QRectF rect = this->rect();
    qreal width = rect.width();
    qreal height = rect.height();

    qreal radius = 5;
    qreal margin = 10;

    QPointF point1(width/2, -margin);
    QPointF point2(width + margin, height/2);
    QPointF point3(width/2, height + margin);
    QPointF point4(-margin, height/2);

    painter->drawEllipse(point1, radius, radius);
    painter->drawEllipse(point2, radius, radius);
    painter->drawEllipse(point3, radius, radius);
    painter->drawEllipse(point4, radius, radius);

    painter->restore();
}

