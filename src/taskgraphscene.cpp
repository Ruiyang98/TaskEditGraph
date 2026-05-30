#include "taskgraphscene.h"
#include "taskmodel.h"
#include "task.h"
#include "tasknodeitem.h"
#include "connectionitem.h"
#include "taskconditiondialog.h"
#include <QInputDialog>
#include <QMessageBox>

TaskGraphScene::TaskGraphScene(QObject *parent)
    : QGraphicsScene(parent)
{
}

TaskGraphScene::~TaskGraphScene()
{
    clearScene();
}

void TaskGraphScene::setTaskModel(TaskModel *model)
{
    if (m_model) {
        disconnect(m_model, nullptr, this, nullptr);
    }

    m_model = model;
    clearScene();

    if (m_model) {
        connect(m_model, &TaskModel::taskAdded, this, &TaskGraphScene::onTaskAdded);
        connect(m_model, &TaskModel::taskRemoved, this, &TaskGraphScene::onTaskRemoved);
        connect(m_model, &TaskModel::taskUpdated, this, &TaskGraphScene::onTaskUpdated);
        connect(m_model, &TaskModel::conditionChanged, this, &TaskGraphScene::onConditionChanged);
        rebuildScene();
    }
}

TaskModel *TaskGraphScene::taskModel() const
{
    return m_model;
}

TaskNodeItem *TaskGraphScene::nodeAt(int index) const
{
    return m_nodes.value(index, nullptr);
}

void TaskGraphScene::refresh()
{
    clearScene();
    rebuildScene();
}

void TaskGraphScene::onTaskAdded(int index)
{
    Q_UNUSED(index)
    refresh();
}

void TaskGraphScene::onTaskRemoved(int index)
{
    Q_UNUSED(index)
    refresh();
}

void TaskGraphScene::onTaskUpdated(int index)
{
    TaskNodeItem *node = m_nodes.value(index, nullptr);
    if (node && m_model) {
        node->setTask(m_model->taskAt(index));
    }
}

void TaskGraphScene::onConditionChanged(int index)
{
    Q_UNUSED(index)
    updateConnections();
}

void TaskGraphScene::onAddTask(int index)
{
    if (!m_model)
        return;

    bool ok;
    QString name = QInputDialog::getText(nullptr, "添加任务", "任务名称:", QLineEdit::Normal, QString(), &ok);
    if (ok && !name.isEmpty()) {
        Task *task = new Task(0, name);
        m_model->addTask(task, index);
    }
}

void TaskGraphScene::onEditTask(int index)
{
    if (!m_model)
        return;

    Task *task = m_model->taskAt(index);
    if (!task)
        return;

    bool ok;
    QString name = QInputDialog::getText(nullptr, "修改任务", "任务名称:", QLineEdit::Normal, task->name(), &ok);
    if (ok && !name.isEmpty()) {
        m_model->updateTask(index, name);
    }
}

void TaskGraphScene::onDeleteTask(int index)
{
    if (!m_model)
        return;

    QMessageBox::StandardButton reply = QMessageBox::question(nullptr, "删除任务",
        "确定要删除该任务吗?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        m_model->removeTask(index);
    }
}

void TaskGraphScene::onSetCondition(int index)
{
    if (!m_model)
        return;

    Task *task = m_model->taskAt(index);
    if (!task)
        return;

    TaskConditionDialog dialog;
    dialog.setCondition(task->condition());
    if (dialog.exec() == QDialog::Accepted) {
        m_model->setTaskCondition(index, dialog.condition());
    }
}

void TaskGraphScene::clearScene()
{
    m_nodes.clear();
    m_connections.clear();
    QGraphicsScene::clear();
}

void TaskGraphScene::rebuildScene()
{
    if (!m_model)
        return;

    int count = m_model->taskCount();
    qreal startX = 50.0;
    qreal startY = 200.0;
    qreal spacing = 200.0;

    for (int i = 0; i < count; ++i) {
        Task *task = m_model->taskAt(i);
        TaskNodeItem *node = new TaskNodeItem();
        node->setTask(task);
        node->setIndex(i);
        node->setPos(startX + i * spacing, startY);
        addItem(node);
        m_nodes.insert(i, node);

        connect(node, &TaskNodeItem::addTaskRequested, this, &TaskGraphScene::onAddTask);
        connect(node, &TaskNodeItem::editTaskRequested, this, &TaskGraphScene::onEditTask);
        connect(node, &TaskNodeItem::deleteTaskRequested, this, &TaskGraphScene::onDeleteTask);
        connect(node, &TaskNodeItem::setConditionRequested, this, &TaskGraphScene::onSetCondition);
    }

    updateConnections();
}

void TaskGraphScene::updateConnections()
{
    for (ConnectionItem *conn : m_connections) {
        removeItem(conn);
        delete conn;
    }
    m_connections.clear();

    if (!m_model)
        return;

    int count = m_model->taskCount();
    for (int i = 0; i < count - 1; ++i) {
        TaskNodeItem *source = m_nodes.value(i, nullptr);
        TaskNodeItem *target = m_nodes.value(i + 1, nullptr);
        if (!source || !target)
            continue;

        ConnectionItem *conn = new ConnectionItem();
        conn->setSourceNode(source);
        conn->setTargetNode(target);

        Task *task = m_model->taskAt(i + 1);
        if (task) {
            conn->setConditionText(task->conditionText());
        }

        addItem(conn);
        m_connections.append(conn);
    }
}
