#include "taskgraphview.h"
#include "taskgraphscene.h"
#include "taskmodel.h"

TaskGraphView::TaskGraphView(QWidget *parent)
    : QGraphicsView(parent)
{
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
    setDragMode(QGraphicsView::ScrollHandDrag);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setResizeAnchor(QGraphicsView::AnchorViewCenter);
}

TaskGraphView::~TaskGraphView()
{
}

void TaskGraphView::setTaskModel(TaskModel *model)
{
    if (!m_scene) {
        m_scene = new TaskGraphScene(this);
        setScene(m_scene);
    }
    m_scene->setTaskModel(model);
}

TaskModel *TaskGraphView::taskModel() const
{
    return m_scene ? m_scene->taskModel() : nullptr;
}
