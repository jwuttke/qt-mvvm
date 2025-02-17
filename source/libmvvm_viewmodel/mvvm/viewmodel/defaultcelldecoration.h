// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_DEFAULTCELLDECORATION_H
#define MVVM_VIEWMODEL_DEFAULTCELLDECORATION_H

#include <mvvm/viewmodel/celldecorationinterface.h>

class QModelIndex;

namespace ModelView
{

//! Generates default cell decorations for Qt trees and tables.

class CORE_EXPORT DefaultCellDecoration : public CellDecorationInterface
{
public:
    bool hasCustomDecoration(const QModelIndex& index) const;
    std::string cellText(const QModelIndex& index) const;
};

} // namespace ModelView

#endif  // MVVM_VIEWMODEL_DEFAULTCELLDECORATION_H
