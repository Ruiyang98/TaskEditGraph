#include "task.h"

Task::Task()
    : m_id(0)
    , m_name()
    , m_status(TaskStatus::Pending)
    , m_condition()
{
}

Task::Task(int id, const QString& name)
    : m_id(id)
    , m_name(name)
    , m_status(TaskStatus::Pending)
    , m_condition()
{
}

int Task::id() const
{
    return m_id;
}

void Task::setId(int id)
{
    m_id = id;
}

QString Task::name() const
{
    return m_name;
}

void Task::setName(const QString& name)
{
    m_name = name;
}

TaskStatus Task::status() const
{
    return m_status;
}

void Task::setStatus(TaskStatus status)
{
    m_status = status;
}

TaskCondition Task::condition() const
{
    return m_condition;
}

void Task::setCondition(const TaskCondition& condition)
{
    m_condition = condition;
}

QColor Task::statusColor() const
{
    switch (m_status) {
    case TaskStatus::Pending:
        return Qt::gray;
    case TaskStatus::Running:
        return QColor(0, 170, 0);
    case TaskStatus::Completed:
        return QColor(0, 100, 200);
    case TaskStatus::Failed:
        return QColor(200, 50, 50);
    }
    return Qt::gray;
}

QString Task::conditionText() const
{
    switch (m_condition.type) {
    case TaskConditionType::AfterDuration:
        return QString("执行%1秒后切换").arg(m_condition.durationSeconds);
    case TaskConditionType::Sequential:
        return QString("顺序执行");
    case TaskConditionType::AtTime:
        return QString("指定时间%1开始").arg(m_condition.startTime);
    }
    return QString();
}
