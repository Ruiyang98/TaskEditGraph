#include "addtaskdialog.h"
#include "ui_addtaskdialog.h"
#include "taskconditiondialog.h"

AddTaskDialog::AddTaskDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddTaskDialog)
{
    ui->setupUi(this);

    ui->statusCombo->addItem(QString::fromLocal8Bit("Pending"), static_cast<int>(TaskStatus::Pending));
    ui->statusCombo->addItem(QString::fromLocal8Bit("Running"), static_cast<int>(TaskStatus::Running));
    ui->statusCombo->addItem(QString::fromLocal8Bit("Completed"), static_cast<int>(TaskStatus::Completed));
    ui->statusCombo->addItem(QString::fromLocal8Bit("Failed"), static_cast<int>(TaskStatus::Failed));

    connect(ui->conditionButton, &QPushButton::clicked,
            this, &AddTaskDialog::onSetConditionClicked);

    updateConditionLabel();
}

AddTaskDialog::~AddTaskDialog()
{
    delete ui;
}

void AddTaskDialog::setTask(Task *task)
{
    if (!task)
        return;

    ui->nameEdit->setText(task->name());

    int statusIndex = 0;
    switch (task->status()) {
    case TaskStatus::Pending: statusIndex = 0; break;
    case TaskStatus::Running: statusIndex = 1; break;
    case TaskStatus::Completed: statusIndex = 2; break;
    case TaskStatus::Failed: statusIndex = 3; break;
    }
    ui->statusCombo->setCurrentIndex(statusIndex);

    m_condition = task->condition();
    updateConditionLabel();
}

Task *AddTaskDialog::createTask() const
{
    QString name = ui->nameEdit->text().trimmed();
    if (name.isEmpty())
        return nullptr;

    TaskStatus status = static_cast<TaskStatus>(ui->statusCombo->currentData().toInt());

    Task *task = new Task(0, name);
    task->setStatus(status);
    task->setCondition(m_condition);
    return task;
}

void AddTaskDialog::onSetConditionClicked()
{
    TaskConditionDialog dialog(this);
    dialog.setCondition(m_condition);
    if (dialog.exec() == QDialog::Accepted) {
        m_condition = dialog.condition();
        updateConditionLabel();
    }
}

void AddTaskDialog::updateConditionLabel()
{
    Task tempTask;
    tempTask.setCondition(m_condition);
    ui->conditionLabel->setText(tempTask.conditionText());
}
