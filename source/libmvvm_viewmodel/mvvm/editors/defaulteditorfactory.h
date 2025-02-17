// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_EDITORS_DEFAULTEDITORFACTORY_H
#define MVVM_EDITORS_DEFAULTEDITORFACTORY_H

#include <mvvm/editors/editorbuilders.h>
#include <mvvm/editors/editorfactoryinterface.h>
#include <map>

namespace ModelView
{

//! Default editor factory for custom variants.
//! Used in context of trees and tables via ViewModelDelegate.

class CORE_EXPORT DefaultEditorFactory : public EditorFactoryInterface
{
public:
    DefaultEditorFactory();
    ~DefaultEditorFactory() override;

    std::unique_ptr<CustomEditor> createEditor(const QModelIndex& index) const override;

protected:
    void registerBuilder(const std::string& name, EditorBuilders::builder_t strategy);
    EditorBuilders::builder_t findBuilder(const std::string& name) const;
    std::map<std::string, EditorBuilders::builder_t> m_editor_builders;
};

} // namespace ModelView

#endif  // MVVM_EDITORS_DEFAULTEDITORFACTORY_H
