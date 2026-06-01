#ifndef TASKCONDITIONDIALOG_H
#define TASKCONDITIONDIALOG_H

#include <QDialog>
#include "task.h"

namespace Ui {
class TaskConditionDialog;
}

class TaskConditionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TaskConditionDialog(QWidget *parent = nullptr);
    ~TaskConditionDialog();

    void setCondition(const TaskCondition &condition);
    TaskCondition condition() const;

private slots:
    void onTypeChanged(int index);

private:
    Ui::TaskConditionDialog *ui;
};

#endif // TASKCONDITIONDIALOG_H
