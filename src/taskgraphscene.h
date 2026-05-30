#ifndef TASKGRAPHSCENE_H
#define TASKGRAPHSCENE_H

#include <QGraphicsScene>
#include <QMap>

class TaskModel;
class TaskNodeItem;
class ConnectionItem;

class TaskGraphScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit TaskGraphScene(QObject *parent = nullptr);
    ~TaskGraphScene();

    void setTaskModel(TaskModel *model);
    TaskModel *taskModel() const;

    TaskNodeItem *nodeAt(int index) const;

    void refresh();

private slots:
    void onTaskAdded(int index);
    void onTaskRemoved(int index);
    void onTaskUpdated(int index);
    void onConditionChanged(int index);

    void onAddTask(int index);
    void onEditTask(int index);
    void onDeleteTask(int index);
    void onSetCondition(int index);

private:
    void clearScene();
    void rebuildScene();
    void updateConnections();

    TaskModel *m_model = nullptr;
    QMap<int, TaskNodeItem *> m_nodes;
    QList<ConnectionItem *> m_connections;
};

#endif // TASKGRAPHSCENE_H
