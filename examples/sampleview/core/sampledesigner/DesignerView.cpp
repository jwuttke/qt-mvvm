// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "DesignerView.h"
#include "DesignerHelper.h"
#include "DesignerMimeData.h"
#include "DesignerScene.h"
#include <QDragEnterEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMimeData>
#include <QShortcut>
#include <QVBoxLayout>

DesignerView::DesignerView(DesignerScene* scene, QWidget* parent)
    : QGraphicsView(scene, parent)
{
    if (!scene)
        throw std::runtime_error("Error in DesignerView: scene is null.");
    setAcceptDrops(true);
    setRenderHint(QPainter::Antialiasing);
    setMouseTracking(true);
    setDragMode(QGraphicsView::RubberBandDrag);
}

int DesignerView::getSelectionMode() const
{
    if (dragMode() == QGraphicsView::NoDrag) {
        return SIMPLE_SELECTION;
    } else if (dragMode() == QGraphicsView::RubberBandDrag) {
        return RUBBER_SELECTION;
    } else if (dragMode() == QGraphicsView::ScrollHandDrag) {
        return HAND_DRAG;
    } else {
        throw std::runtime_error("DesignerView::getSelectionMode() -> Error.");
    }
}

void DesignerView::onSelectionMode(int mode)
{
    switch (mode) {
    case SIMPLE_SELECTION:
        setDragMode(QGraphicsView::NoDrag);
        setInteractive(true);
        emit selectionModeChanged(SIMPLE_SELECTION);
        break;
    case RUBBER_SELECTION:
        setDragMode(QGraphicsView::RubberBandDrag);
        setInteractive(true);
        emit selectionModeChanged(RUBBER_SELECTION);
        break;
    case HAND_DRAG:
        setDragMode(QGraphicsView::ScrollHandDrag);
        setInteractive(false);
        emit selectionModeChanged(HAND_DRAG);
        break;
    default:
        break;
    }
}

void DesignerView::onCenterView()
{
    // fitInView(scene()->itemsBoundingRect() ,Qt::KeepAspectRatio);
    centerOn(scene()->itemsBoundingRect().center());
}

void DesignerView::onChangeScale(double new_scale)
{
    QMatrix oldMatrix = matrix();
    resetMatrix();
    translate(oldMatrix.dx(), oldMatrix.dy());
    scale(new_scale, new_scale);
    DesignerHelper::setZoomLevel(new_scale);
}

void DesignerView::deleteSelected()
{
    designerScene()->modelController().remove(designerScene()->selectedItems());
}

void DesignerView::copySelected()
{
    designerScene()->modelController().copy(designerScene()->selectedItems());
}

void DesignerView::pasteSelected()
{
    designerScene()->modelController().paste();
}

void DesignerView::zoomIn()
{
}

void DesignerView::zoomOut()
{
}

void DesignerView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        break;
    case Qt::Key_Space:
        if (getSelectionMode() != HAND_DRAG && !event->isAutoRepeat()) {
            onSelectionMode(HAND_DRAG);
        }
        break;
    case Qt::Key_Delete:
    case Qt::Key_Backspace:
        deleteSelected();
        break;
    case Qt::Key_C:
        if (event->modifiers() == Qt::ControlModifier)
            copySelected();
        break;
    case Qt::Key_V:
        if (event->modifiers() == Qt::ControlModifier)
            pasteSelected();
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}

void DesignerView::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Space:

        if (getSelectionMode() != RUBBER_SELECTION && !event->isAutoRepeat()) {
            onSelectionMode(RUBBER_SELECTION); // space released
        }
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}

DesignerScene *DesignerView::designerScene() const
{
    return dynamic_cast<DesignerScene*>(scene());
}
