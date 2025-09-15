#ifndef CONNECTIONBUTTON_H
#define CONNECTIONBUTTON_H

#include <QObject>
#include <QGraphicsObject>
#include <QPainter>
#include <QDebug>

class ConnectionButton : public QGraphicsObject
{
    Q_OBJECT
public:
    ConnectionButton();
    QRectF boundingRect() const override;
    void setText(QString newText);
    QString text();

signals:
    void pressed();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    virtual bool event(QEvent *ev) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    QString currentText = "";
    QRectF ellipseItem;
};

#endif // CONNECTIONBUTTON_H
