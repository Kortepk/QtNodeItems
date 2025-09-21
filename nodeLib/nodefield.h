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
    Q_OBJECT
public:
    explicit NodeField(QWidget *parent = nullptr);
    NodeField(QGraphicsScene *scene, QWidget *parent = nullptr);
    void addItem(QGraphicsItem *item);
    void addNode(NodeItem *node);

protected slots:
    void linkTwoNode(QPair<QString, int> node1, QPair<QString, int> node2);

protected:
    void generalInit();
    void initLine();
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

    QPointF getCenterScenePos();
    QPoint m_lastMousePos;
    bool m_isPanning;

    QGraphicsLineItem *cursorLine = nullptr;
    QPointF startConnectPos;

    QMap<QString, NodeItem *> nodeMap; // <id, object>
    QMap<QString, QGraphicsLineItem *> connectionLine; // <id, line>
};

#endif // NODEFIELD_H
