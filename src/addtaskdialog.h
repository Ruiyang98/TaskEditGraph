#ifndef ADDTASKDIALOG_H
#define ADDTASKDIALOG_H

#include <QDialog>
#include "task.h"

namespace Ui {
class AddTaskDialog;
}

class AddTaskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTaskDialog(QWidget *parent = nullptr);
    ~AddTaskDialog();

    void setTask(Task *task);
    Task *createTask() const;

private slots:
    void onSetConditionClicked();

private:
    void updateConditionLabel();

    Ui::AddTaskDialog *ui;
    TaskCondition m_condition;
};

#endif // ADDTASKDIALOG_H
