#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QColor>

enum class TaskStatus {
    Pending,
    Running,
    Completed,
    Failed
};

enum class TaskConditionType {
    AfterDuration,
    Sequential,
    AtTime
};

struct TaskCondition {
    TaskConditionType type;
    int durationSeconds;
    QString startTime;

    TaskCondition()
        : type(TaskConditionType::Sequential)
        , durationSeconds(0)
        , startTime()
    {
    }
};

class Task
{
public:
    Task();
    explicit Task(int id, const QString& name);

    int id() const;
    void setId(int id);

    QString name() const;
    void setName(const QString& name);

    TaskStatus status() const;
    void setStatus(TaskStatus status);

    TaskCondition condition() const;
    void setCondition(const TaskCondition& condition);

    QColor statusColor() const;
    QString conditionText() const;

private:
    int m_id;
    QString m_name;
    TaskStatus m_status;
    TaskCondition m_condition;
};

#endif // TASK_H
