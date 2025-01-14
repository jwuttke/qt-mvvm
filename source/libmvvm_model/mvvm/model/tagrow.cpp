// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/model/tagrow.h>

//! Returns TagRow corresponding to the append to tag_name.
//! If tag_name =="" the default name will be used in SessionItemTags context.

ModelView::TagRow ModelView::TagRow::append(const std::string& tag_name)
{
    return {tag_name, -1};
}

//! Returns TagRow corresponding to prepending to tag_name.
//! If tag_name =="" the default name will be used in SessionItemTags context.

ModelView::TagRow ModelView::TagRow::prepend(const std::string& tag_name)
{
    return {tag_name, 0};
}

bool ModelView::TagRow::operator==(const ModelView::TagRow& other) const
{
    return row == other.row && tag==other.tag;
}

bool ModelView::TagRow::operator!=(const ModelView::TagRow& other) const
{
    return !(*this == other);
}
