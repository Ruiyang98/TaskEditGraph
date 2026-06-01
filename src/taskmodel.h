#ifndef TASKMODEL_H
#define TASKMODEL_H

#include <QObject>
#include <QList>
#include "task.h"

class TaskModel : public QObject
{
    Q_OBJECT

public:
    explicit TaskModel(QObject *parent = nullptr);
    ~TaskModel();

    void addTask(Task *task, int afterIndex = -1);
    void removeTask(int index);
    void updateTask(int index, const QString &name);
    void updateTask(int index, const QString &name, TaskStatus status, const TaskCondition &condition);
    void setTaskCondition(int index, const TaskCondition &condition);

    Task *taskAt(int index) const;
    int taskCount() const;
    QList<Task *> tasks() const;
    void clear();

signals:
    void taskAdded(int index);
    void taskRemoved(int index);
    void taskUpdated(int index);
    void conditionChanged(int index);

private:
    QList<Task *> m_tasks;
};

#endif // TASKMODEL_H
