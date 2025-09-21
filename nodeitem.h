#ifndef NODEITEM_H
#define NODEITEM_H
#include <QWidget>
#include <QPushButton>
#include <QDrag>
#include <QMimeData>
#include "nodetable.h"
#include "connectionbutton.h"

#define BUTTON_COUNT 4

class NodeItem : public QWidget
{
    Q_OBJECT
public:
    explicit NodeItem(QWidget *parent = nullptr);
    NodeItem(qreal x, qreal y, qreal width, qreal height, QWidget *parent = nullptr);
    void generalInit();

    void setText(QString newText);
    void setNodeId(QString newNodeId);
    void setBrush(QBrush newBrush);
    void addConectionLine(QGraphicsLineItem *newLine, int butIndex, bool isBegin, NodeItem *otherNode);
    void removeLink(QGraphicsLineItem *line);

    QString getNodeId();
    NodeTable *getTable();
    QPointF getDragStartPos();
    QVector<ConnectionButton *> getConnectionButton();

signals:
    void createLinkNode(QPair<QString, int> node1, QPair<QString, int> node2); // For connection line
    void destroyedConectionLine(QGraphicsLineItem *line);

protected:
    void tableDestroyedHandler();

    QString TitleText;
    QString NodeId;
    QBrush tableBrush;
    NodeTable *mainTable;
    QVector<ConnectionButton *> conBut;
    QVector<QGraphicsLineItem *> conLine;
    QVector<bool> beginPoint;
    QVector<NodeItem *> conNode;
    QPointF conButtonStartPos;

protected slots:
    void moveConButtons(QPointF newPos);
    void doteClicked(int butIndex);
    void bindNodeHandler(int index, QPair<QString, int> sender);
};

#endif // NODEITEM_H
