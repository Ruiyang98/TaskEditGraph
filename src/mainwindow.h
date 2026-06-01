#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class TaskGraphView;
class TaskModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void createDemoTasks();

    TaskGraphView *m_graphView = nullptr;
    TaskModel *m_taskModel = nullptr;
};

#endif
