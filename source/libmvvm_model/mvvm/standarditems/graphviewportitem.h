// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_STANDARDITEMS_GRAPHVIEWPORTITEM_H
#define MVVM_STANDARDITEMS_GRAPHVIEWPORTITEM_H

#include <mvvm/standarditems/viewportitem.h>

namespace ModelView
{

class GraphItem;

/*!
@class GraphViewportItem
@brief Container with viewport and collection of GraphItem's to plot.
*/

class CORE_EXPORT GraphViewportItem : public ViewportItem
{
public:
    GraphViewportItem();

    std::vector<GraphItem*> graphItems() const;

private:
    std::pair<double, double> data_xaxis_range() const override;
    std::pair<double, double> data_yaxis_range() const override;
};

} // namespace ModelView

#endif  // MVVM_STANDARDITEMS_GRAPHVIEWPORTITEM_H
