#include "settingslistmodel.h"

SettingsListModel::SettingsListModel(QObject* pobj):
    QAbstractListModel(pobj)
{

}


QVariant SettingsListModel::data(const QModelIndex& index, int role) const
{
    QIcon m_emptyIcon;

    if (!index.isValid()) {
        return QVariant();
    }
    switch (role) {
        case Qt::DisplayRole: {
        return m_list.at(index.row())->displayName();
    }

        case Qt::DecorationRole: {
                   QIcon icon = m_list.at(index.row())->icon;
                   if (icon.isNull())
                       icon = m_emptyIcon;
                   return icon;
               }
    }
    return QVariant();
}


int SettingsListModel::rowCount(const QModelIndex& parent) const
{
    return m_list.size();
}

void SettingsListModel::setPages(QList<ISettingsPage*> pages)
{
    m_list.clear();

    for(auto &page : pages) {
        SettingsListItem* item = new SettingsListItem(page);
        m_list.append(item);
    }

}
