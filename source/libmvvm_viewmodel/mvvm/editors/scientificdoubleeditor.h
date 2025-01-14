// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_EDITORS_SCIENTIFICDOUBLEEDITOR_H
#define MVVM_EDITORS_SCIENTIFICDOUBLEEDITOR_H

#include <mvvm/editors/customeditor.h>

class QLineEdit;
class QDoubleValidator;

namespace ModelView
{

//! Custom editor for QVariant based on double with scientific notation support.

class CORE_EXPORT ScientificDoubleEditor : public CustomEditor
{
public:
    explicit ScientificDoubleEditor(QWidget* parent = nullptr);

    void setRange(double minimum, double maximum);

private slots:
    void onEditingFinished();

private:
    void update_components() override;
    QLineEdit* m_lineEdit;
    QDoubleValidator* m_validator{nullptr};
};

} // namespace ModelView

#endif  // MVVM_EDITORS_SCIENTIFICDOUBLEEDITOR_H
