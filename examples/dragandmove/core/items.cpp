// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "items.h"
#include "item_constants.h"
#include "comboproperty.h"
#include "externalproperty.h"
#include <QColor>

using namespace ModelView;

const std::string DemoItem::P_BOOL_PROPERTY = "P_BOOL_PROPERTY";
const std::string DemoItem::P_INTEGER_PROPERTY = "P_INTEGER_PROPERTY";
const std::string DemoItem::P_STRING_PROPERTY = "P_STRING_PROPERTY";
const std::string DemoItem::P_DOUBLE_PROPERTY = "P_DOUBLE_PROPERTY";
const std::string DemoItem::P_COLOR_PROPERTY = "P_COLOR_PROPERTY";
const std::string DemoItem::P_COMBO_PROPERTY = "P_COMBO_PROPERTY";
const std::string DemoItem::P_EXTERNAL_PROPERTY = "P_EXTERNAL_PROPERTY";

DemoItem::DemoItem() : CompoundItem(::Constants::DemoItemType)
{
    addProperty<>(P_BOOL_PROPERTY, true)->setDisplayName("Bool");
    addProperty<>(P_INTEGER_PROPERTY, 42)->setDisplayName("Integer");
    addProperty<>(P_STRING_PROPERTY, "abc")->setDisplayName("String");
    addProperty<>(P_DOUBLE_PROPERTY, 42.1)->setDisplayName("Double");
    addProperty<>(P_COLOR_PROPERTY, QColor(Qt::green))->setDisplayName("Color");

    ComboProperty combo = ComboProperty() << "option 1" << "option 2" << "option 3";
    addProperty<>(P_COMBO_PROPERTY, QVariant::fromValue(combo))->setDisplayName("Combo");

    ExternalProperty ext_prop = ExternalProperty("Gold", QColor(Qt::darkYellow), "some id");
    addProperty<>(P_EXTERNAL_PROPERTY, QVariant::fromValue(ext_prop))->setDisplayName("External");
}

// ----------------------------------------------------------------------------


const std::string DemoContainerItem::T_ITEMS = "T_ITEMS";

DemoContainerItem::DemoContainerItem() : CompoundItem(::Constants::DemoContainerItemType)
{
    registerTag(TagInfo::universalTag(T_ITEMS, {::Constants::DemoItemType}),/*set_default*/true);
}
