// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DESIGNERVIEW_H
#define DESIGNERVIEW_H

#include<QGraphicsView>

class DesignerScene;
class QGraphicsView;
class QDragEnterEvent;
class QWheelEvent;
class QKeyEvent;

//! The DesignerView class provides widget for displaying the contents of DesignerScene
//!
//! Belongs to SampleDesigner
//! Currently contains logic for zooming, deleting objects
class DesignerView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit DesignerView(DesignerScene* scene, QWidget* parent = nullptr);
    virtual ~DesignerView(){}

    enum ESelectionModes { SIMPLE_SELECTION, RUBBER_SELECTION, HAND_DRAG};
    int getSelectionMode() const;

    void onSelectionMode(int);
    void onCenterView();
    void onChangeScale(double);
    void deleteSelected();
    void copySelected();
    void pasteSelected();

    void zoomIn();
    void zoomOut();

signals:
    void selectionModeChanged(int);

protected:
//    void wheelEvent(QWheelEvent *event);
//    void scaleView(qreal scaleFactor);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    DesignerScene* designerScene() const;
};

#endif // DESIGNERVIEW_H
