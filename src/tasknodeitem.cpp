#include "tasknodeitem.h"
#include "task.h"
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>

TaskNodeItem::TaskNodeItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
}

void TaskNodeItem::setTask(Task *task)
{
    m_task = task;
    update();
}

Task *TaskNodeItem::task() const
{
    return m_task;
}

void TaskNodeItem::setIndex(int index)
{
    m_index = index;
}

int TaskNodeItem::index() const
{
    return m_index;
}

QRectF TaskNodeItem::boundingRect() const
{
    return QRectF(0, 0, s_width, s_height);
}

void TaskNodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QColor borderColor = m_task ? m_task->statusColor() : QColor(200, 200, 200);
    QColor fillColor = QColor(245, 245, 245);

    QRectF rect(0, 0, s_width, s_height);
    QPainterPath path;
    path.addRoundedRect(rect, s_radius, s_radius);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillPath(path, fillColor);

    QPen pen(borderColor);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->drawPath(path);

    QString name = m_task ? m_task->name() : QString("Task");
    QString statusText = m_task ? QString::fromStdString(
        [](TaskStatus s) {
            switch (s) {
            case TaskStatus::Pending: return "Pending";
            case TaskStatus::Running: return "Running";
            case TaskStatus::Completed: return "Completed";
            case TaskStatus::Failed: return "Failed";
            }
            return "";
        }(m_task->status())) : QString("");

    painter->setPen(Qt::black);
    QFont font = painter->font();
    font.setPointSize(10);
    font.setBold(true);
    painter->setFont(font);
    painter->drawText(rect, Qt::AlignHCenter | Qt::AlignTop, name);

    QFont smallFont = painter->font();
    smallFont.setPointSize(8);
    smallFont.setBold(false);
    painter->setFont(smallFont);
    painter->drawText(rect.adjusted(0, 30, 0, 0), Qt::AlignHCenter | Qt::AlignTop, statusText);
}

void TaskNodeItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    QAction *addAction = menu.addAction("添加任务");
    QAction *editAction = menu.addAction("修改任务");
    QAction *deleteAction = menu.addAction("删除任务");
    QAction *conditionAction = menu.addAction("设置切换条件");

    QAction *selected = menu.exec(event->screenPos());
    if (selected == addAction) {
        emit addTaskRequested(m_index);
    } else if (selected == editAction) {
        emit editTaskRequested(m_index);
    } else if (selected == deleteAction) {
        emit deleteTaskRequested(m_index);
    } else if (selected == conditionAction) {
        emit setConditionRequested(m_index);
    }
}
