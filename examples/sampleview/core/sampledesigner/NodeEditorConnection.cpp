// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "NodeEditorConnection.h"
#include "ConnectableView.h"
#include "NodeEditorPort.h"
#include <QBrush>
#include <QGraphicsScene>
#include <QPainter>
#include <QPen>

NodeEditorConnection::NodeEditorConnection(QGraphicsScene* scene)
    : QGraphicsPathItem()
    , m_port1(nullptr)
    , m_port2(nullptr)
{
    if (!scene)
        throw std::runtime_error(
            "Error in NodeEditorConnection::NodeEditorConnection: passed scene pointer is null.");
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setPen(QPen(Qt::darkGray, 2));
    setBrush(Qt::NoBrush);
    setZValue(-1);
    scene->addItem(this);
}


NodeEditorConnection::~NodeEditorConnection()
{
    if (m_port1)
        m_port1->remove(this);

    if (m_port2)
        m_port2->remove(this);
}

void NodeEditorConnection::setPos1(const QPointF &p)
{
    pos1 = p;
}

void NodeEditorConnection::setPos2(const QPointF &p)
{
    pos2 = p;
}

void NodeEditorConnection::setPort1(NodeEditorPort *p)
{
    m_port1 = p;
    m_port1->append(this);
    setPos1(p->scenePos());
}

void NodeEditorConnection::setPort2(NodeEditorPort *p)
{
    m_port2 = p;
    m_port2->append(this);
    setPos2(p->scenePos());
}

void NodeEditorConnection::updatePosFromPorts()
{
    pos1 = m_port1->scenePos();
    pos2 = m_port2->scenePos();
}

void NodeEditorConnection::updatePath()
{
    QPainterPath p;
    p.moveTo(pos1);
    qreal dx = pos2.x() - pos1.x();
    dx = qMax(dx, 200.);
    QPointF ctr1(pos1.x() + dx * 0.25, pos1.y() );
    QPointF ctr2(pos2.x() - dx * 0.25, pos2.y() );
    p.cubicTo(ctr1, ctr2, pos2);
    setPath(p);
}

NodeEditorPort* NodeEditorConnection::port1() const
{
    return m_port1;
}

NodeEditorPort* NodeEditorConnection::port2() const
{
    return m_port2;
}

NodeEditorPort *NodeEditorConnection::inputPort()
{
    Q_ASSERT(m_port1 && m_port2);
    return (m_port1->isInput() ? m_port1 : m_port2);
}

NodeEditorPort *NodeEditorConnection::outputPort()
{
    Q_ASSERT(m_port1 && m_port2);
    return (m_port1->isOutput() ? m_port1 : m_port2);
}

void NodeEditorConnection::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setPen(QPen(Qt::darkGray, 2));
    painter->setBrush(Qt::NoBrush);

    if (isSelected())
        painter->setPen(Qt::DashLine);

    painter->drawPath(path());
}

ConnectableView *NodeEditorConnection::getParentView()
{
    Q_ASSERT(inputPort() != outputPort());
    ConnectableView *result = dynamic_cast<ConnectableView *>(inputPort()->parentItem());
    Q_ASSERT(result);
    return result;
}

ConnectableView *NodeEditorConnection::getChildView()
{
    Q_ASSERT(inputPort() != outputPort());
    ConnectableView *result = dynamic_cast<ConnectableView *>(outputPort()->parentItem());
    Q_ASSERT(result);
    return result;
}
