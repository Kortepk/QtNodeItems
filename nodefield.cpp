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

void NodeField::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QGraphicsItem* item = itemAt(event->pos());

        if (item && item->flags() & QGraphicsItem::ItemIsMovable) {
            QGraphicsView::mousePressEvent(event);
        } else {
            m_isPanning = true;
            m_lastMousePos = event->pos();
            setCursor(Qt::ClosedHandCursor);
            event->accept();
            return;
        }
    }
    QGraphicsView::mousePressEvent(event);
}

void NodeField::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isPanning) {
        QPoint delta = event->pos() - m_lastMousePos;
        m_lastMousePos = event->pos();

        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
        verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());

        event->accept();
    } else {
        QGraphicsView::mouseMoveEvent(event);
    }
}

void NodeField::mouseReleaseEvent(QMouseEvent *event)
{
    if ((event->button() == Qt::LeftButton) && m_isPanning) {
        m_isPanning = false;
        setCursor(Qt::ArrowCursor);
        event->accept();
    } else {
        QGraphicsView::mouseReleaseEvent(event);
    }
}
