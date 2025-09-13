#include "nodefield.h"

NodeField::NodeField(QWidget *parent)
    : QGraphicsView(parent)
{

}

NodeField::NodeField(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
{

}

void NodeField::wheelEvent(QWheelEvent *event)
{
    static qreal scaleTotal = 1;

    qreal scaleOld = scaleTotal;
    qreal scaleFactor = 1;

    if(event->angleDelta().y() > 0){
        scaleTotal += 0.1;
    }
    else{
        scaleTotal -= 0.1;
    }

    if(scaleTotal < 0.1)
        scaleTotal = 0.1;

    scaleFactor = scaleTotal/scaleOld;
    scale(scaleFactor, scaleFactor);

    //qDebug() << scaleTotal << scaleFactor;

    QGraphicsView::wheelEvent(event);
}

void NodeField::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->fillRect(rect, Qt::white);

    painter->setPen(QColor(210, 210, 210));

    int m_gridSize = 50;

    qreal x = int(rect.left()) - (int(rect.left()) % m_gridSize);
    qreal y = int(rect.top()) - (int(rect.top()) % m_gridSize);

    QVector<QLineF> lines;

    while(x < rect.right()){
        lines.append(QLineF(x, rect.top(), x, rect.bottom()));
        x += m_gridSize;
    }

    while(y < rect.bottom()){
        lines.append(QLineF(rect.left(), y, rect.right(), y));
        y += m_gridSize;
    }

    painter->drawLines(lines);
}
