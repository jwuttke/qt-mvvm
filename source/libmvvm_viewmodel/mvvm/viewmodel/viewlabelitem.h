// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_VIEWLABELITEM_H
#define MVVM_VIEWMODEL_VIEWLABELITEM_H

#include <mvvm/viewmodel/viewitem.h>

namespace ModelView
{

class SessionItem;

//! Represents display name of SessionItem in any cell of Qt's trees and tables.

class CORE_EXPORT ViewLabelItem : public ViewItem
{
public:
    explicit ViewLabelItem(SessionItem* item);
    int type() const override;

    QVariant data(int role) const override;
};

} // namespace ModelView

#endif  // MVVM_VIEWMODEL_VIEWLABELITEM_H
