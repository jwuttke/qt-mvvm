// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MATERIALSELECTORCELLEDITOR_H
#define MATERIALSELECTORCELLEDITOR_H

#include <mvvm/editors/customeditor.h>

class QComboBox;
class QStandardItemModel;
class MaterialModel;

/*!
@class MaterialSelectorCellEditor
@brief Custom editor for table cells to select material from the list of existing materials.

FIXME: move editor itself (which is combo box with colors) to separate widget independend
from model.
*/

class MaterialSelectorCellEditor : public ModelView::CustomEditor
{
public:
    explicit MaterialSelectorCellEditor(MaterialModel* model, QWidget* parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

protected slots:
    virtual void onIndexChanged(int index);

private:
    int internIndex();
    void setConnected(bool isConnected);
    void update_components() override;
    QComboBox* m_box;
    MaterialModel* m_model;
    QStandardItemModel* m_combo_model;
};

#endif // MATERIALSELECTORCELLEDITOR_H
