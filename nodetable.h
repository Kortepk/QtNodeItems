#ifndef NODETABLE_H
#define NODETABLE_H
#include <QObject>
#include <QGraphicsObject>
#include <QPen>
#include <QRadioButton>
#include <QGraphicsSceneMouseEvent>
#include <QRect>
#include "QDebug"

class NodeTable : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit NodeTable();
    NodeTable(qreal x, qreal y, qreal width, qreal height);
    void setNodeId(QString newNodeId);
    QString nodeId();
    void setText(QString newText);
    QString text();
    void setBrush(QBrush newBrush);
    QRectF boundingRect() const override;

signals:
    void newPosition(QPointF newPos);

protected:
    void generalInit();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    virtual bool event(QEvent *ev) override;

    QString NodeId = "";
    QString TitleText = "";
    QFont nodeFont;
    QBrush mainBrush;
    QRectF rectItem;

};

#endif // NODETABLE_H
