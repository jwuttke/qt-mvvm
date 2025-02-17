// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PLOTTING_COLORMAPCANVAS_H
#define MVVM_PLOTTING_COLORMAPCANVAS_H

#include <mvvm/core/export.h>
#include <memory>
#include <QWidget>

namespace ModelView
{

class ColorMapViewportItem;

/*!
@class ColorMapCanvas
@brief Widget to show 2D data as color map.

Contains embedded QCustomPlot widget, shows content of ColorMapViewportItem.
*/

class CORE_EXPORT ColorMapCanvas : public QWidget
{
public:
    explicit ColorMapCanvas(QWidget* parent = nullptr);
    ~ColorMapCanvas() override;

    void setItem(ColorMapViewportItem* viewport_item);

private:
    struct ColorMapCanvasImpl;
    std::unique_ptr<ColorMapCanvasImpl> p_impl;
};

} // namespace ModelView

#endif  // MVVM_PLOTTING_COLORMAPCANVAS_H
