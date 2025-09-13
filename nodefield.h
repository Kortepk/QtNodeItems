#ifndef NODEFIELD_H
#define NODEFIELD_H

#include <QGraphicsView>
#include <QObject>
#include <QWidget>
#include <QWheelEvent>
#include <QDebug>
#include <QScrollBar>
#include <QGraphicsItem>
#include <QRect>

class NodeField : public QGraphicsView
{
public:
    explicit NodeField(QWidget *parent = nullptr);
    NodeField(QGraphicsScene *scene, QWidget *parent = nullptr);
    void addItem(QGraphicsItem *item);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    QPointF getCenterScenePos();
    QPoint m_lastMousePos;
    bool m_isPanning;
};

#endif // NODEFIELD_H
