#include "mainwindow.h"
#include "taskgraphview.h"
#include "taskmodel.h"
#include "task.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("任务编辑界面"));
    resize(800, 600);

    m_taskModel = new TaskModel(this);

    Task *task1 = new Task(1, "任务1");
    Task *task2 = new Task(2, "任务2");
    Task *task3 = new Task(3, "任务3");

    task2->setStatus(TaskStatus::Running);
    task3->setStatus(TaskStatus::Pending);

    TaskCondition cond1;
    cond1.type = TaskConditionType::AfterDuration;
    cond1.durationSeconds = 10;
    task1->setCondition(cond1);

    TaskCondition cond2;
    cond2.type = TaskConditionType::Sequential;
    task2->setCondition(cond2);

    m_taskModel->addTask(task1);
    m_taskModel->addTask(task2);
    m_taskModel->addTask(task3);

    m_graphView = new TaskGraphView(this);
    m_graphView->setTaskModel(m_taskModel);

    setCentralWidget(m_graphView);
}
