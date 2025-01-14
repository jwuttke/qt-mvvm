// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_EDITORS_CUSTOMEDITOR_H
#define MVVM_EDITORS_CUSTOMEDITOR_H

#include <mvvm/core/export.h>
#include <QWidget>
#include <QVariant>

namespace ModelView
{

//! Base class for all custom variant editors.

class CORE_EXPORT CustomEditor : public QWidget
{
    Q_OBJECT

public:
    explicit CustomEditor(QWidget* parent = nullptr);

    QVariant data() const;

    virtual bool is_persistent() const;

public slots:
    void setData(const QVariant& data);

signals:
    //! Emmits signal when data was changed in an editor.
    void dataChanged();

protected:
    void setDataIntern(const QVariant& data);
    //! Should update widget components from m_data, if necessary.
    virtual void update_components() = 0;
    QVariant m_data;
};

} // namespace ModelView

#endif  // MVVM_EDITORS_CUSTOMEDITOR_H
