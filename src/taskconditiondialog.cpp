#include "taskconditiondialog.h"
#include "ui_taskconditiondialog.h"
#include <QRegExpValidator>

TaskConditionDialog::TaskConditionDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TaskConditionDialog)
{
    ui->setupUi(this);

    QRegExpValidator *timeValidator = new QRegExpValidator(QRegExp("([0-1]?[0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])"), this);
    ui->timeEdit->setValidator(timeValidator);

    connect(ui->typeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &TaskConditionDialog::onTypeChanged);

    onTypeChanged(0);
}

TaskConditionDialog::~TaskConditionDialog()
{
    delete ui;
}

void TaskConditionDialog::onTypeChanged(int index)
{
    ui->paramStack->setCurrentIndex(index);
}

void TaskConditionDialog::setCondition(const TaskCondition &condition)
{
    int typeIndex = 0;
    switch (condition.type) {
    case TaskConditionType::Sequential:
        typeIndex = 0;
        break;
    case TaskConditionType::AfterDuration:
        typeIndex = 1;
        break;
    case TaskConditionType::AtTime:
        typeIndex = 2;
        break;
    }
    ui->typeCombo->setCurrentIndex(typeIndex);
    ui->durationSpin->setValue(condition.durationSeconds > 0 ? condition.durationSeconds : 1);
    ui->timeEdit->setText(condition.startTime);
}

TaskCondition TaskConditionDialog::condition() const
{
    TaskCondition cond;
    int typeIndex = ui->typeCombo->currentIndex();
    switch (typeIndex) {
    case 0:
        cond.type = TaskConditionType::Sequential;
        break;
    case 1:
        cond.type = TaskConditionType::AfterDuration;
        break;
    case 2:
        cond.type = TaskConditionType::AtTime;
        break;
    }
    cond.durationSeconds = ui->durationSpin->value();
    cond.startTime = ui->timeEdit->text();
    return cond;
}
