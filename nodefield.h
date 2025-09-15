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
#include <QGraphicsProxyWidget>
#include "nodeitem.h"

class NodeField : public QGraphicsView
{
public:
    explicit NodeField(QWidget *parent = nullptr);
    NodeField(QGraphicsScene *scene, QWidget *parent = nullptr);
    void addItem(QGraphicsItem *item);
    void addNode(NodeItem *node);

protected:
    void generalInit();
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;

    QPointF getCenterScenePos();
    QPoint m_lastMousePos;
    bool m_isPanning;
};

#endif // NODEFIELD_H
