#ifndef TASKEDITHELPER_H
#define TASKEDITHELPER_H

class TaskModel;
class QWidget;

class TaskEditHelper
{
public:
    static bool addTaskInteractive(TaskModel *model, QWidget *parent = nullptr, int afterIndex = -1);
    static bool editTaskInteractive(TaskModel *model, int index, QWidget *parent = nullptr);
};

#endif // TASKEDITHELPER_H
