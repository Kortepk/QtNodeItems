#ifndef CONNECTIONBUTTON_H
#define CONNECTIONBUTTON_H

#include <QObject>
#include <QGraphicsObject>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>

class ConnectionButton : public QGraphicsObject
{
    Q_OBJECT
public:
    ConnectionButton();
    ConnectionButton(int index);
    QRectF boundingRect() const override;
    void setText(QString newText);

    QString text();
    int getIndex();

signals:
    void pressed(int butIndex);
    void dropNodeHere(int index, QPair<QString, int> sender);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    virtual bool event(QEvent *ev) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;

    QString currentText = "";
    QRectF ellipseItem;
    int butIndex = -1;
    bool mousePressed = false;
};

#endif // CONNECTIONBUTTON_H
