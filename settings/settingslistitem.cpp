#include "settingslistitem.h"

SettingsListItem::SettingsListItem(ISettingsPage* page, QObject *parent) :
    QObject(parent)
    , m_page(page) {
    m_displayName = m_page->displayName();
}

QString SettingsListItem::displayName() const {
    return m_displayName;
}

QTabWidget* SettingsListItem::widget() const {
    return m_tabWidget;
}
