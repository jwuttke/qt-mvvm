// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PLOTTING_COLORMAPVIEWPORTPLOTCONTROLLER_H
#define MVVM_PLOTTING_COLORMAPVIEWPORTPLOTCONTROLLER_H

#include <mvvm/signals/itemcontroller.h>
#include <memory>

class QCustomPlot;

namespace ModelView
{

class ColorMapViewportItem;

/*!
@class ColorMapViewportPlotController
@brief Establishes communications and mutual updates for ColorMapViewportItem and QCutomPlot.

Populates custom plot with color map and tracks updates in items.
*/

class CORE_EXPORT ColorMapViewportPlotController : public ItemController<ColorMapViewportItem>
{
public:
    explicit ColorMapViewportPlotController(QCustomPlot* plot);
    ~ColorMapViewportPlotController() override;

protected:
    void subscribe() override;
    void unsubscribe() override;

private:
    struct ColorMapViewportPlotControllerImpl;
    std::unique_ptr<ColorMapViewportPlotControllerImpl> p_impl;
};

} // namespace ModelView

#endif  // MVVM_PLOTTING_COLORMAPVIEWPORTPLOTCONTROLLER_H
