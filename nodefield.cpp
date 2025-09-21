#include "nodefield.h"

NodeField::NodeField(QWidget *parent)
    : QGraphicsView(parent)
{
    generalInit();
}

NodeField::NodeField(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
{
    generalInit();
}

void NodeField::generalInit()
{
    setAcceptDrops(true);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setRenderHint(QPainter::Antialiasing, true);
}

void NodeField::initLine()
{
    cursorLine = new QGraphicsLineItem(QLineF(startConnectPos, startConnectPos));
    cursorLine->setPen(QPen(QColor(71, 138, 255), 2, Qt::DashLine));
    scene()->addItem(cursorLine);
}

void NodeField::wheelEvent(QWheelEvent *event)
{
    static qreal scaleTotal = 1;

    qreal scaleOld = scaleTotal;
    qreal scaleFactor = 1;

    if(event->angleDelta().y() > 0){
        scaleTotal += 0.1;
    }
    else{
        scaleTotal -= 0.1;
    }

    if(scaleTotal < 0.1)
        scaleTotal = 0.1;

    scaleFactor = scaleTotal/scaleOld;
    scale(scaleFactor, scaleFactor);

    //qDebug() << scaleTotal << scaleFactor;

    QGraphicsView::wheelEvent(event);
}

void NodeField::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->fillRect(rect, Qt::white);

    painter->setPen(QColor(210, 210, 210));

    int m_gridSize = 50;

    qreal x = int(rect.left()) - (int(rect.left()) % m_gridSize);
    qreal y = int(rect.top()) - (int(rect.top()) % m_gridSize);

    QVector<QLineF> lines;

    while(x < rect.right()){
        lines.append(QLineF(x, rect.top(), x, rect.bottom()));
        x += m_gridSize;
    }

    while(y < rect.bottom()){
        lines.append(QLineF(rect.left(), y, rect.right(), y));
        y += m_gridSize;
    }

    painter->drawLines(lines);
}

void NodeField::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QGraphicsItem* item = itemAt(event->pos());

        if (item && (item->flags() & (QGraphicsItem::ItemIsMovable |
                                      QGraphicsItem::ItemIsFocusScope)))
        {
            QGraphicsView::mousePressEvent(event);
        } else {
            m_isPanning = true;
            m_lastMousePos = event->pos();
            setCursor(Qt::ClosedHandCursor);
            event->accept();
            return;
        }
    }
    QGraphicsView::mousePressEvent(event);
}

void NodeField::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isPanning) {
        QPoint delta = event->pos() - m_lastMousePos;
        m_lastMousePos = event->pos();

        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
        verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());

        event->accept();
    } else {
        QGraphicsView::mouseMoveEvent(event);
    }
}

void NodeField::mouseReleaseEvent(QMouseEvent *event)
{
    if ((event->button() == Qt::LeftButton) && m_isPanning) {
        m_isPanning = false;
        setCursor(Qt::ArrowCursor);
        event->accept();
    } else {
        QGraphicsView::mouseReleaseEvent(event);
    }
}

void NodeField::dragEnterEvent(QDragEnterEvent *event)
{
    QGraphicsView::dragEnterEvent(event);

    if (event->mimeData()->hasFormat("application/node-data")) {
        //int butIndex = event->mimeData()->hasFormat("application/node-data");
        QString nodeId = event->mimeData()->text();

        if(nodeMap.contains(nodeId)){
            event->acceptProposedAction();

            startConnectPos = nodeMap[nodeId]->getDragStartPos();

            if (!cursorLine)
                initLine();
        }
    } else
        event->ignore();
}

void NodeField::dragLeaveEvent(QDragLeaveEvent *event)
{
    QGraphicsView::dragLeaveEvent(event);
}

void NodeField::dragMoveEvent(QDragMoveEvent *event)
{
    QGraphicsView::dragMoveEvent(event); // child handle event

    if (event->mimeData()->hasFormat("application/node-data")) {
        event->acceptProposedAction();
        if (cursorLine) {
            QPointF mousePos = mapToScene(event->pos());
            cursorLine->setLine(QLineF(startConnectPos, mousePos));
        }
    } else {
        event->ignore();
    }
}

void NodeField::dropEvent(QDropEvent *event)
{
    QGraphicsView::dropEvent(event);

    if (cursorLine != nullptr) {
        delete cursorLine;
        cursorLine = nullptr;
    }
}

QPointF NodeField::getCenterScenePos()
{
    QPoint viewportCenter(viewport()->width() / 2, viewport()->height() / 2);
    return mapToScene(viewportCenter);
}

void NodeField::addItem(QGraphicsItem *item)
{
    QPointF newPos = getCenterScenePos();
    QRectF itemRect = item->boundingRect();

    newPos -= QPointF(itemRect.width()/2, itemRect.height()/2);

    item->setPos(newPos);

    scene()->addItem(item);
}

void NodeField::addNode(NodeItem *node)
{
    QPointF newPos = getCenterScenePos();
    NodeTable *nt = node->getTable();
    QRectF itemRect = nt->boundingRect();

    newPos -= QPointF(itemRect.width()/2, itemRect.height()/2);
    nt->setPos(newPos);

    scene()->addItem(node->getTable());

    nodeMap[node->getNodeId()] = node;
    connect(node, &NodeItem::createLinkNode, this, &NodeField::linkTwoNode);

    QVector<ConnectionButton *> butVect = node->getConnectionButton();

    for(int i = 0; i < butVect.length(); i++){
        scene()->addItem(butVect[i]);
    }

}

void NodeField::linkTwoNode(QPair<QString, int> node1, QPair<QString, int> node2)
{
    nodeMap[node1.first]->addConectionLine(cursorLine, node1.second, false, nodeMap[node2.first]);
    nodeMap[node2.first]->addConectionLine(cursorLine, node2.second, true, nodeMap[node1.first]);

    cursorLine = nullptr;
}
