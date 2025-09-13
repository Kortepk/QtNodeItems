#ifndef NODEITEM_H
#define NODEITEM_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QWidget>
#include <QPen>
#include <QRadioButton>

class NodeItem : public QGraphicsRectItem
{
public:
    explicit NodeItem(QGraphicsItem *parent = nullptr);
    NodeItem(const QRectF &customRect, QGraphicsItem *parent = nullptr);
    NodeItem(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);
    void setNodeId(QString newNodeId);
    QString nodeId();
    void setText(QString newText);
    QString text();
    //QVector<QRadioButton *> getConnectionButton();

protected:
    void generalInit();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    QString NodeId = "";
    QString TitleText = "";
    QFont nodeFont;
};

#endif // NODEITEM_H
