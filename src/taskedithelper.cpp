#include "taskedithelper.h"
#include "taskmodel.h"
#include "task.h"
#include "addtaskdialog.h"

bool TaskEditHelper::addTaskInteractive(TaskModel *model, QWidget *parent, int afterIndex)
{
    if (!model)
        return false;

    AddTaskDialog dialog(parent);
    if (dialog.exec() != QDialog::Accepted)
        return false;

    Task *task = dialog.createTask();
    if (!task)
        return false;

    model->addTask(task, afterIndex);
    return true;
}

bool TaskEditHelper::editTaskInteractive(TaskModel *model, int index, QWidget *parent)
{
    if (!model)
        return false;

    Task *task = model->taskAt(index);
    if (!task)
        return false;

    AddTaskDialog dialog(parent);
    dialog.setTask(task);
    if (dialog.exec() != QDialog::Accepted)
        return false;

    Task *newTask = dialog.createTask();
    if (!newTask)
        return false;

    model->updateTask(index, newTask->name(), newTask->status(), newTask->condition());
    delete newTask;
    return true;
}
