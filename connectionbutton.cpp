#include "connectionbutton.h"

ConnectionButton::ConnectionButton() {
    ellipseItem.setRect(0, 0, 12, 12);
    setAcceptDrops(true);

    setFlag(ItemIsFocusScope , true);
    setFlag(ItemIsFocusable, true);
    setFlag(ItemSendsScenePositionChanges, true);
    setAcceptHoverEvents(true);
}

ConnectionButton::ConnectionButton(int index) {
    ellipseItem.setRect(0, 0, 12, 12);
    setAcceptDrops(true);

    setFlag(ItemIsFocusScope , true);
    setFlag(ItemIsFocusable, true);
    setFlag(ItemSendsScenePositionChanges, true);
    setAcceptHoverEvents(true);

    butIndex = index;
}

void ConnectionButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    mousePressed = true;
    emit pressed(butIndex);
    ConnectionButton::mouseReleaseEvent(event);
}

void ConnectionButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mouseReleaseEvent(event);
    mousePressed = false;
}

void ConnectionButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(mousePressed) // Border
        painter->setPen(QPen(QColor(148, 173, 211), 2));
    else
        painter->setPen(QPen(QColor(29, 58, 107), 2));

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

int ConnectionButton::getIndex()
{
    return butIndex;
}

void ConnectionButton::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    QGraphicsObject::dragEnterEvent(event);

    if (event->mimeData()->hasFormat("application/node-data")) {
        event->acceptProposedAction();
    } else
        event->ignore();
}

void ConnectionButton::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    QGraphicsObject::dropEvent(event);

    if (event->mimeData()->hasFormat("application/node-data")) {
        int butIn = event->mimeData()->data("application/node-data").toInt();
        QString nodeId = event->mimeData()->text();

        event->acceptProposedAction();

        emit dropNodeHere(butIndex, {nodeId, butIn});
    }
}
