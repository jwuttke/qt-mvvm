// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PLOTTING_DATA2DPLOTCONTROLLER_H
#define MVVM_PLOTTING_DATA2DPLOTCONTROLLER_H

#include <mvvm/signals/itemcontroller.h>
#include <memory>

class QCPColorMap;

namespace ModelView
{

class Data2DItem;

/*!
@class Data2DPlotController
@brief Establish communication between QCPColorMap and Data2DItem.

Provide update of data points on QCPColorMap when Graph2DItem is changed.
*/

class CORE_EXPORT Data2DPlotController : public ItemController<Data2DItem>
{
public:
    explicit Data2DPlotController(QCPColorMap* color_map);
    ~Data2DPlotController() override;

protected:
    void subscribe() override;
    void unsubscribe() override;

private:
    struct Data2DPlotControllerImpl;
    std::unique_ptr<Data2DPlotControllerImpl> p_impl;
};

} // namespace ModelView

#endif  // MVVM_PLOTTING_DATA2DPLOTCONTROLLER_H
