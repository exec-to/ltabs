#include "settingslistitem.h"

SettingsListItem::SettingsListItem(ISettingsPage* page, QObject *parent) :
    QObject(parent)
    , m_page(page)
    , m_widget(nullptr)
{
    m_displayName = m_page->displayName();
    m_widget = m_page->page();
    m_icon = QIcon(*(m_page->displayIcon()));
}

QString SettingsListItem::displayName() const {
    return m_displayName;
}

QWidget* SettingsListItem::widget() const {
    return m_widget;
}

QIcon SettingsListItem::icon() {
    return m_icon;
}
