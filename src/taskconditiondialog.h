#ifndef TASKCONDITIONDIALOG_H
#define TASKCONDITIONDIALOG_H

#include <QDialog>
#include "task.h"

class QComboBox;
class QStackedWidget;
class QSpinBox;
class QLineEdit;
class QPushButton;

class TaskConditionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TaskConditionDialog(QWidget *parent = nullptr);

    void setCondition(const TaskCondition &condition);
    TaskCondition condition() const;

private slots:
    void onTypeChanged(int index);

private:
    void setupUi();

    QComboBox *m_typeCombo;
    QStackedWidget *m_paramStack;
    QSpinBox *m_durationSpin;
    QLineEdit *m_timeEdit;
    QPushButton *m_okButton;
    QPushButton *m_cancelButton;
};

#endif // TASKCONDITIONDIALOG_H
