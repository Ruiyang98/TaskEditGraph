#ifndef TASKNODEITEM_H
#define TASKNODEITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QObject>

class Task;

class TaskNodeItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    explicit TaskNodeItem(QGraphicsItem *parent = nullptr);

    void setTask(Task *task);
    Task *task() const;

    void setIndex(int index);
    int index() const;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

signals:
    void addTaskRequested(int index);
    void editTaskRequested(int index);
    void deleteTaskRequested(int index);
    void setConditionRequested(int index);

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

private:
    Task *m_task = nullptr;
    int m_index = -1;
    static constexpr qreal s_width = 140.0;
    static constexpr qreal s_height = 70.0;
    static constexpr qreal s_radius = 8.0;
};

#endif // TASKNODEITEM_H
