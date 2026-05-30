#ifndef CONNECTIONITEM_H
#define CONNECTIONITEM_H

#include <QGraphicsItem>
#include <QPainter>

class TaskNodeItem;

class ConnectionItem : public QGraphicsItem
{
public:
    explicit ConnectionItem(QGraphicsItem *parent = nullptr);

    void setSourceNode(TaskNodeItem *node);
    TaskNodeItem *sourceNode() const;

    void setTargetNode(TaskNodeItem *node);
    TaskNodeItem *targetNode() const;

    void setConditionText(const QString &text);
    QString conditionText() const;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    void updateBoundingRect();

    TaskNodeItem *m_sourceNode = nullptr;
    TaskNodeItem *m_targetNode = nullptr;
    QString m_conditionText;
    QRectF m_boundingRect;
};

#endif // CONNECTIONITEM_H
