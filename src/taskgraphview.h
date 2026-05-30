#ifndef TASKGRAPHVIEW_H
#define TASKGRAPHVIEW_H

#include <QGraphicsView>

class TaskModel;
class TaskGraphScene;

class TaskGraphView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit TaskGraphView(QWidget *parent = nullptr);
    ~TaskGraphView();

    void setTaskModel(TaskModel *model);
    TaskModel *taskModel() const;

private:
    TaskGraphScene *m_scene = nullptr;
};

#endif // TASKGRAPHVIEW_H
