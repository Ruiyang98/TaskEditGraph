#include "connectionitem.h"
#include "tasknodeitem.h"
#include <QtMath>
#include <QApplication>
#include <QFontMetrics>

ConnectionItem::ConnectionItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
}

void ConnectionItem::setSourceNode(TaskNodeItem *node)
{
    m_sourceNode = node;
    updateBoundingRect();
    update();
}

TaskNodeItem *ConnectionItem::sourceNode() const
{
    return m_sourceNode;
}

void ConnectionItem::setTargetNode(TaskNodeItem *node)
{
    m_targetNode = node;
    updateBoundingRect();
    update();
}

TaskNodeItem *ConnectionItem::targetNode() const
{
    return m_targetNode;
}

void ConnectionItem::setConditionText(const QString &text)
{
    m_conditionText = text;
    updateBoundingRect();
    update();
}

QString ConnectionItem::conditionText() const
{
    return m_conditionText;
}

QRectF ConnectionItem::boundingRect() const
{
    return m_boundingRect;
}

void ConnectionItem::updateBoundingRect()
{
    if (!m_sourceNode || !m_targetNode) {
        m_boundingRect = QRectF();
        return;
    }

    QPointF sourcePos = m_sourceNode->scenePos() + QPointF(m_sourceNode->boundingRect().width(), m_sourceNode->boundingRect().height() / 2.0);
    QPointF targetPos = m_targetNode->scenePos() + QPointF(0, m_targetNode->boundingRect().height() / 2.0);

    qreal left = qMin(sourcePos.x(), targetPos.x());
    qreal top = qMin(sourcePos.y(), targetPos.y());
    qreal right = qMax(sourcePos.x(), targetPos.x());
    qreal bottom = qMax(sourcePos.y(), targetPos.y());

    qreal margin = 20.0;
    if (!m_conditionText.isEmpty()) {
        QFontMetrics fm(QApplication::font());
        QRect textRect = fm.boundingRect(m_conditionText);
        margin = qMax(margin, textRect.height() / 2.0 + 5.0);
    }

    m_boundingRect = QRectF(left - margin, top - margin, right - left + margin * 2, bottom - top + margin * 2);
}

void ConnectionItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    if (!m_sourceNode || !m_targetNode)
        return;

    QPointF sourcePos = m_sourceNode->scenePos() + QPointF(m_sourceNode->boundingRect().width(), m_sourceNode->boundingRect().height() / 2.0);
    QPointF targetPos = m_targetNode->scenePos() + QPointF(0, m_targetNode->boundingRect().height() / 2.0);

    QLineF line(sourcePos, targetPos);

    painter->setRenderHint(QPainter::Antialiasing);
    QPen pen(QColor(120, 120, 120));
    pen.setWidth(2);
    painter->setPen(pen);
    painter->drawLine(line);

    qreal arrowSize = 10.0;
    qreal angle = std::atan2(-line.dy(), line.dx());

    QPointF arrowP1 = targetPos + QPointF(std::sin(angle + M_PI / 3) * arrowSize, std::cos(angle + M_PI / 3) * arrowSize);
    QPointF arrowP2 = targetPos + QPointF(std::sin(angle + M_PI - M_PI / 3) * arrowSize, std::cos(angle + M_PI - M_PI / 3) * arrowSize);

    QPolygonF arrowHead;
    arrowHead << targetPos << arrowP1 << arrowP2;

    painter->setBrush(QColor(120, 120, 120));
    painter->drawPolygon(arrowHead);

    if (!m_conditionText.isEmpty()) {
        QPointF midPoint = (sourcePos + targetPos) / 2.0;
        painter->setPen(Qt::black);
        QFont font = painter->font();
        font.setPointSize(8);
        painter->setFont(font);
        painter->drawText(midPoint + QPointF(5, -5), m_conditionText);
    }
}
