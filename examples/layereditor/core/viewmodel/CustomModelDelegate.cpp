// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "CustomModelDelegate.h"
#include "CustomEditorFactory.h"
#include "CustomCellDecoration.h"

using namespace ModelView;

CustomModelDelegate::CustomModelDelegate(ApplicationModels* models, QObject* parent)
    : ViewModelDelegate(parent)
{
    setEditorFactory(std::make_unique<CustomEditorFactory>(models));
}
