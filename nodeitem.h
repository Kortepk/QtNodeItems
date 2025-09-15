#ifndef NODEITEM_H
#define NODEITEM_H
#include <QWidget>
#include <QPushButton>
#include "nodetable.h"

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
    NodeTable *getTable();
    QVector<QPushButton *> getConnectionButton();

protected:
    QString TitleText;
    QString NodeId;
    QBrush tableBrush;
    NodeTable *mainTable;
    QVector<QPushButton *> conBut;

protected slots:
    void moveConButtons(QPointF newPos);

};

#endif // NODEITEM_H
