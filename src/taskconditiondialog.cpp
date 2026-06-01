#include "taskconditiondialog.h"
#include <QComboBox>
#include <QStackedWidget>
#include <QSpinBox>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QRegExpValidator>

TaskConditionDialog::TaskConditionDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi();
    setWindowTitle(QString::fromLocal8Bit("设置任务切换条件"));
}

void TaskConditionDialog::setupUi()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *typeLabel = new QLabel(QString::fromLocal8Bit("条件类型:"), this);
    m_typeCombo = new QComboBox(this);
    m_typeCombo->addItem(QString::fromLocal8Bit("顺序执行"), static_cast<int>(TaskConditionType::Sequential));
    m_typeCombo->addItem(QString::fromLocal8Bit("执行指定时间后切换"), static_cast<int>(TaskConditionType::AfterDuration));
    m_typeCombo->addItem(QString::fromLocal8Bit("指定时间开始切换"), static_cast<int>(TaskConditionType::AtTime));

    QHBoxLayout *typeLayout = new QHBoxLayout();
    typeLayout->addWidget(typeLabel);
    typeLayout->addWidget(m_typeCombo);
    mainLayout->addLayout(typeLayout);

    m_paramStack = new QStackedWidget(this);

    QWidget *sequentialPage = new QWidget(this);
    QVBoxLayout *sequentialLayout = new QVBoxLayout(sequentialPage);
    sequentialLayout->addWidget(new QLabel(QString::fromLocal8Bit("无额外参数"), this));
    sequentialLayout->addStretch();
    m_paramStack->addWidget(sequentialPage);

    QWidget *durationPage = new QWidget(this);
    QHBoxLayout *durationLayout = new QHBoxLayout(durationPage);
    durationLayout->addWidget(new QLabel(QString::fromLocal8Bit("持续时间(秒):"), this));
    m_durationSpin = new QSpinBox(this);
    m_durationSpin->setRange(1, 99999);
    m_durationSpin->setValue(1);
    durationLayout->addWidget(m_durationSpin);
    durationLayout->addStretch();
    m_paramStack->addWidget(durationPage);

    QWidget *timePage = new QWidget(this);
    QHBoxLayout *timeLayout = new QHBoxLayout(timePage);
    timeLayout->addWidget(new QLabel("开始时间:", this));
    m_timeEdit = new QLineEdit(this);
    m_timeEdit->setPlaceholderText("HH:MM:SS");
    QRegExpValidator *timeValidator = new QRegExpValidator(QRegExp("([0-1]?[0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])"), this);
    m_timeEdit->setValidator(timeValidator);
    timeLayout->addWidget(m_timeEdit);
    timeLayout->addStretch();
    m_paramStack->addWidget(timePage);

    mainLayout->addWidget(m_paramStack);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    m_okButton = new QPushButton(QString::fromLocal8Bit("确定"), this);
    m_cancelButton = new QPushButton(QString::fromLocal8Bit("取消"), this);
    buttonLayout->addWidget(m_okButton);
    buttonLayout->addWidget(m_cancelButton);
    mainLayout->addLayout(buttonLayout);

    connect(m_typeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &TaskConditionDialog::onTypeChanged);
    connect(m_okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(m_cancelButton, &QPushButton::clicked, this, &QDialog::reject);

    onTypeChanged(0);
}

void TaskConditionDialog::onTypeChanged(int index)
{
    m_paramStack->setCurrentIndex(index);
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
    m_typeCombo->setCurrentIndex(typeIndex);
    m_durationSpin->setValue(condition.durationSeconds > 0 ? condition.durationSeconds : 1);
    m_timeEdit->setText(condition.startTime);
}

TaskCondition TaskConditionDialog::condition() const
{
    TaskCondition cond;
    int typeIndex = m_typeCombo->currentIndex();
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
    cond.durationSeconds = m_durationSpin->value();
    cond.startTime = m_timeEdit->text();
    return cond;
}
