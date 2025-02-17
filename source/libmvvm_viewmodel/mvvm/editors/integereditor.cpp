// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/editors/integereditor.h>
#include <QSpinBox>
#include <QVBoxLayout>

using namespace ModelView;

IntegerEditor::IntegerEditor(QWidget* parent) : CustomEditor(parent), m_intEditor(new QSpinBox)
{
    setAutoFillBackground(true);
    m_intEditor->setFocusPolicy(Qt::StrongFocus);
    m_intEditor->setKeyboardTracking(false);

    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(m_intEditor);

    connect(m_intEditor, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            [=] { this->onEditingFinished(); });

    setLayout(layout);

    setFocusProxy(m_intEditor);
}

void IntegerEditor::setRange(int minimum, int maximum)
{
    m_intEditor->setMinimum(minimum);
    m_intEditor->setMaximum(maximum);
}

void IntegerEditor::onEditingFinished()
{
    int new_value = m_intEditor->value();
    if (new_value != m_data.value<int>())
        setDataIntern(QVariant::fromValue(new_value));
}

void IntegerEditor::update_components()
{
    if (m_data.type() != QVariant::Int)
        throw std::runtime_error("IntegerEditor::update_components() -> Error. Wrong variant type");

    m_intEditor->setValue(m_data.value<int>());
}
