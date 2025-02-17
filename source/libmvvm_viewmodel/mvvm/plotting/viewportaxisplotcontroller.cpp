// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/plotting/viewportaxisplotcontroller.h>
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/signals/itemmapper.h>
#include "qcustomplot.h"
#include <mvvm/plotting/customplotutils.h>
#include <QObject>

using namespace ModelView;

struct ViewportAxisPlotController::AxesPlotControllerImpl {

    ViewportAxisPlotController* controller{nullptr};
    QCPAxis* axis{nullptr};
    bool block_update{false};
    std::unique_ptr<QMetaObject::Connection> axis_conn;

    AxesPlotControllerImpl(ViewportAxisPlotController* controller, QCPAxis* axis)
        : controller(controller), axis(axis)
    {
        if (!axis)
            throw std::runtime_error("AxisPlotController: axis is not initialized.");
        axis_conn = std::make_unique<QMetaObject::Connection>();
    }

    //! Connects QCustomPlot signals with controller methods.
    void setConnected()
    {

        auto on_axis_range = [this](const QCPRange& newRange) {
            block_update = true;
            auto item = controller->currentItem();
            item->set_range(newRange.lower, newRange.upper);
            block_update = false;
        };

        *axis_conn = QObject::connect(
            axis, static_cast<void (QCPAxis::*)(const QCPRange&)>(&QCPAxis::rangeChanged),
            on_axis_range);
    }

    //! Disonnects QCustomPlot signals.
    void setDisconnected() { QObject::disconnect(*axis_conn); }

    //! Sets axesRange from SessionItem.
    void setAxisRangeFromItem()
    {
        auto [lower, upper] = controller->currentItem()->range();
        axis->setRange(QCPRange(lower, upper));
    }

    void update_log_scale()
    {
        Utils::SetLogarithmicScale(axis, controller->currentItem()->is_in_log());
    }

};

ViewportAxisPlotController::ViewportAxisPlotController(QCPAxis* axis)
    : p_impl(std::make_unique<AxesPlotControllerImpl>(this, axis))

{
}

ViewportAxisPlotController::~ViewportAxisPlotController() = default;

void ViewportAxisPlotController::subscribe()
{
    p_impl->setAxisRangeFromItem();

    auto on_property_change = [this](SessionItem* item, std::string name) {
        if (p_impl->block_update)
            return;

        if (name == ViewportAxisItem::P_MIN)
            p_impl->axis->setRangeLower(item->property(name).value<double>());

        if (name == ViewportAxisItem::P_MAX)
            p_impl->axis->setRangeUpper(item->property(name).value<double>());

        if (name == ViewportAxisItem::P_IS_LOG)
            p_impl->update_log_scale();

        p_impl->axis->parentPlot()->replot();
    };
    currentItem()->mapper()->setOnPropertyChange(on_property_change, this);

    p_impl->setConnected();
}
