#include "taskmodel.h"

TaskModel::TaskModel(QObject *parent)
    : QObject(parent)
{
}

TaskModel::~TaskModel()
{
    clear();
}

void TaskModel::addTask(Task *task, int afterIndex)
{
    if (!task)
        return;

    int insertIndex;
    if (afterIndex < 0 || afterIndex >= m_tasks.size()) {
        insertIndex = m_tasks.size();
        m_tasks.append(task);
    } else {
        insertIndex = afterIndex + 1;
        m_tasks.insert(insertIndex, task);
    }

    emit taskAdded(insertIndex);
}

void TaskModel::removeTask(int index)
{
    if (index < 0 || index >= m_tasks.size())
        return;

    Task *task = m_tasks.takeAt(index);
    delete task;

    emit taskRemoved(index);
}

void TaskModel::updateTask(int index, const QString &name)
{
    if (index < 0 || index >= m_tasks.size())
        return;

    m_tasks[index]->setName(name);
    emit taskUpdated(index);
}

void TaskModel::updateTask(int index, const QString &name, TaskStatus status, const TaskCondition &condition)
{
    if (index < 0 || index >= m_tasks.size())
        return;

    Task *task = m_tasks[index];
    task->setName(name);
    task->setStatus(status);
    task->setCondition(condition);
    emit taskUpdated(index);
    emit conditionChanged(index);
}

void TaskModel::setTaskCondition(int index, const TaskCondition &condition)
{
    if (index < 0 || index >= m_tasks.size())
        return;

    m_tasks[index]->setCondition(condition);
    emit conditionChanged(index);
}

Task *TaskModel::taskAt(int index) const
{
    if (index < 0 || index >= m_tasks.size())
        return nullptr;

    return m_tasks[index];
}

int TaskModel::taskCount() const
{
    return m_tasks.size();
}

QList<Task *> TaskModel::tasks() const
{
    return m_tasks;
}

void TaskModel::clear()
{
    qDeleteAll(m_tasks);
    m_tasks.clear();
}
