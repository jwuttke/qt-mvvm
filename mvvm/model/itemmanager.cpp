// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "itemmanager.h"
#include "sessionitem.h"
#include "itempool.h"
#include "itemfactory.h"
#include "jsonconverterinterfaces.h"
#include "jsonmodel.h"

using namespace ModelView;

ItemManager::ItemManager()
    : m_item_factory(new ItemFactory)
    , m_converter(new JsonModel)
{

}

void ItemManager::setItemPool(std::shared_ptr<ItemPool> pool)
{
    m_item_pool = pool;
}

ItemManager::~ItemManager() = default;

SessionItem* ItemManager::createItem(const model_type& modelType)
{
    auto result = m_item_factory->createItem(modelType);
    if (m_item_pool)
        result->register_item(m_item_pool);
    return result;
}

SessionItem* ItemManager::createRootItem()
{
    auto result = m_item_factory->createEmptyItem();
    if (m_item_pool)
        result->register_item(m_item_pool);
    return result;
}

SessionItem* ItemManager::findItem(identifier_type id) const
{
    return m_item_pool ? m_item_pool->item_for_key(id) : nullptr;
}

identifier_type ItemManager::findIdentifier(SessionItem* item) const
{
    return m_item_pool ? m_item_pool->key_for_item(item) : identifier_type();
}

const ItemPool* ItemManager::itemPool() const
{
    return m_item_pool.get();
}

const JsonModelInterface& ItemManager::converter() const
{
    return *m_converter.get();
}

//! Replacing existing registration in item pool with new id.

void ItemManager::fix_registration(SessionItem* item, identifier_type id)
{
    m_item_pool->deregister_item(item);
    m_item_pool->register_item(item, id);
}
