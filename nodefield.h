#ifndef NODEFIELD_H
#define NODEFIELD_H

#include <QGraphicsView>
#include <QObject>
#include <QWidget>

class NodeField : public QGraphicsView
{
public:
    explicit NodeField(QWidget *parent = nullptr);
    NodeField(QGraphicsScene *scene, QWidget *parent = nullptr);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;

};

#endif // NODEFIELD_H
