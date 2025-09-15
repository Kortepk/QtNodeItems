#include "connectionbutton.h"

ConnectionButton::ConnectionButton() {
    qDebug() << __PRETTY_FUNCTION__;
    ellipseItem.setRect(0, 0, 12, 12);
    setFlag(ItemIsFocusScope , true);
}

void ConnectionButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << __PRETTY_FUNCTION__;
    QGraphicsObject::mousePressEvent(event);
    emit pressed();
}

void ConnectionButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black, 2)); // Border

    painter->drawEllipse(ellipseItem);
}


QRectF ConnectionButton::boundingRect() const
{
    return ellipseItem;
}

bool ConnectionButton::event(QEvent *ev)
{
    return QObject::event(ev);
}

void ConnectionButton::setText(QString newText)
{
    currentText = newText;
}

QString ConnectionButton::text()
{
    return currentText;
}
