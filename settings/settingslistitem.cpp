#include "settingslistitem.h"

SettingsListItem::SettingsListItem(ISettingsPage* page, QObject *parent) :
    QObject(parent)
    , m_page(page)
    , m_Widget(nullptr)
{
    m_displayName = m_page->displayName();
    m_Widget = m_page->page();
}

QString SettingsListItem::displayName() const {
    return m_displayName;
}

QWidget* SettingsListItem::widget() const {
    return m_Widget;
}
