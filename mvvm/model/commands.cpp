// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "commands.h"
#include "sessionmodel.h"
#include "sessionitem.h"
#include "jsonmodel.h"
#include "itemmanager.h"
#include <QJsonObject>

using namespace ModelView;

SetValueCommand::SetValueCommand(SessionItem* item, const QVariant& value, int role)
    : m_value(value)
    , m_role(role)
    , m_model(item->model())
{
    Q_ASSERT(m_model);
    m_path = m_model->pathFromItem(item);
}

void SetValueCommand::undo()
{
    auto item = m_model->itemFromPath(m_path);
    QVariant old = item->data(m_role);
    item->setDataIntern(m_value, m_role);
    m_value = old;
}

void SetValueCommand::redo()
{
    auto item = m_model->itemFromPath(m_path);
    QVariant old = item->data(m_role);
    item->setDataIntern(m_value, m_role);
    m_value = old;
}

// ----------------------------------------------------------------------------

InsertNewItemCommand::InsertNewItemCommand(const model_type& modelType, SessionItem* parent, int row)
    : m_row(row)
    , m_model_type(modelType)
    , m_model(parent->model())
{
    m_parent_path = m_model->pathFromItem(parent);
}

void InsertNewItemCommand::undo()
{
    auto parent = m_model->itemFromPath(m_parent_path);
    delete parent->takeRow(m_row);
}

void InsertNewItemCommand::redo()
{
    auto parent = m_model->itemFromPath(m_parent_path);
    auto child = m_model->manager()->createItem(m_model_type);
    parent->insertItem(m_row, child);
}


// ----------------------------------------------------------------------------

RemoveRowCommand::RemoveRowCommand(SessionItem* parent, int row)
    : m_row(row)
    , m_model(parent->model())
{
    Q_ASSERT(m_model);
    m_parent_path = m_model->pathFromItem(parent);
}

void RemoveRowCommand::undo()
{
    m_model->setCommandRecordPause(true);

    const auto& converter = m_model->manager()->converter();

    auto parent = m_model->itemFromPath(m_parent_path);
    converter.json_to_item(*m_child_backup, parent, m_row);

    m_model->setCommandRecordPause(false);
}

void RemoveRowCommand::redo()
{
    m_model->setCommandRecordPause(true);

    const auto& converter = m_model->manager()->converter();
    m_child_backup.reset(new QJsonObject);

    auto parent = m_model->itemFromPath(m_parent_path);
    auto child = parent->childAt(m_row);
    converter.item_to_json(child, *m_child_backup);
    delete parent->takeRow(m_row);

    m_model->setCommandRecordPause(false);
}
