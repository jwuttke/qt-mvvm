// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/model/sessionitemdata.h>
#include <mvvm/model/customvariants.h>
#include <sstream>

using namespace ModelView;

std::vector<int> SessionItemData::roles() const
{
    std::vector<int> result;
    for (const auto& value : m_values)
        result.push_back(value.m_role);
    return result;
}

QVariant SessionItemData::data(int role) const
{
    for (const auto& value : m_values) {
        if (value.m_role == role)
            return value.m_data;
    }
    return QVariant();
}

//! Sets the data for given role. Returns true if data was changed.
//! If variant is invalid, corresponding role will be removed.

bool SessionItemData::setData(const QVariant& value, int role)
{
    assure_validity(value, role);

    for (auto it = m_values.begin(); it != m_values.end(); ++it) {
        if (it->m_role == role) {
            if (value.isValid()) {
                if (Utils::IsTheSame(it->m_data, value))
                    return false;
                it->m_data = value;
            } else {
                m_values.erase(it);
            }
            return true;
        }
    }
    m_values.push_back(DataRole(value, role));
    return true;
}

SessionItemData::const_iterator SessionItemData::begin() const
{
    return m_values.begin();
}

SessionItemData::const_iterator SessionItemData::end() const
{
    return m_values.end();
}

//! Check if variant is compatible

void SessionItemData::assure_validity(const QVariant& variant, int role)
{
    if (variant.typeName() == QStringLiteral("QString"))
        throw std::runtime_error("Attempt to set QString based variant");

    if (!Utils::CompatibleVariantTypes(data(role), variant)) {
        std::ostringstream ostr;
        ostr << "SessionItemData::assure_validity() -> Error. Variant types mismatch. "
             << "Old variant type '" << data(role).typeName() << "' "
             << "new variant type '" << variant.typeName() << "\n";
        throw std::runtime_error(ostr.str());
    }
}
