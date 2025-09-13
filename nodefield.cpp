#include "nodefield.h"

NodeField::NodeField(QWidget *parent)
    : QGraphicsView(parent)
{

}

NodeField::NodeField(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
{

}

void NodeField::drawBackground(QPainter *painter, const QRectF &rect)
{
    // Рисуем стандартный фон (белый)
    painter->fillRect(rect, Qt::white);

    // Рисуем сетку
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
