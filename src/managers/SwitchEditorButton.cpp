#include "SwitchEditorButton.h"

#include <QButtonGroup>
#include <QPushButton>

SwitchEditorButton::SwitchEditorButton() : m_group(new QButtonGroup)
{
    m_group->setExclusive(true);
}

SwitchEditorButton& SwitchEditorButton::instance()
{
    static SwitchEditorButton instance;
    return instance;
}

void SwitchEditorButton::addButton(QPushButton* btn, int id)
{
    if (!btn || m_group->buttons().contains(btn)) return;

    if(id == -1)
      id = m_group->buttons().count();

    m_group->addButton(btn, id);

    connect(btn, &QObject::destroyed, this, [this, btn]() {
        removeButton(btn);
    });

    emit buttonAdded(btn);
}

void SwitchEditorButton::removeButton(QPushButton* btn)
{
    if (!btn || !m_group->buttons().contains(btn)) return;

    m_group->removeButton(btn);
    emit buttonRemoved(btn);
}

void SwitchEditorButton::clear()
{
    for (auto* btn : m_group->buttons()) {
        m_group->removeButton(btn);
    }
}

bool SwitchEditorButton::contains(QPushButton* btn) const
{
    return m_group->buttons().contains(btn);
}

QList<QAbstractButton*> SwitchEditorButton::buttons() const
{
    return m_group->buttons();
}

QButtonGroup* SwitchEditorButton::buttonGroup() const
{
    return m_group;
}

QAbstractButton* SwitchEditorButton::button(int id) const
{
    return m_group->button(id);
}

QPushButton* SwitchEditorButton::buttonAsPushButton(int id) const
{
    auto* btn = m_group->button(id);
    return qobject_cast<QPushButton*>(btn);
}

int SwitchEditorButton::checkedId() const
{
    return m_group->checkedId();
}
