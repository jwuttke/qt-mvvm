// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PLOTTING_CUSTOMPLOTUTILS_H
#define MVVM_PLOTTING_CUSTOMPLOTUTILS_H

#include <mvvm/core/export.h>

class QCPColorScale;
class QCPAxis;

namespace ModelView
{

namespace Utils
{

//! Switch axis to logarithmic scale mode.

CORE_EXPORT void SetLogarithmicScale(QCPColorScale* axis, bool is_log_scale);

//! Switch axis to logarithmic scale mode.

CORE_EXPORT void SetLogarithmicScale(QCPAxis* axis, bool isLogz);

} // namespace Utils

} // namespace ModelView

#endif  // MVVM_PLOTTING_CUSTOMPLOTUTILS_H
