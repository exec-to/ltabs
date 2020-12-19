#include "settingslistmodel.h"

SettingsListModel::SettingsListModel(QObject *pobj):
    QAbstractListModel(pobj)
{

}


QVariant SettingsListModel::data(const QModelIndex &index, int role) const
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
           QIcon icon = m_list.at(index.row())->displayIcon();
           if (icon.isNull())
               icon = m_emptyIcon;
           return icon;
        }
    }
    return QVariant();
}


int SettingsListModel::rowCount(const QModelIndex &parent) const
{
    parent.isValid();
    return m_list.size();
}


QWidget* SettingsListModel::getPageByIndex(const QModelIndex &index) const {
    if (index.isValid()) {
        return m_list.at(index.row())->page();
    }
    return new QLabel(tr("Страница не найдена."));
}


void SettingsListModel::setPages(QList<IApplicationPlugin*> plugins)
{
    m_list.clear();

    for(auto &plugin : plugins) {
        m_list.append(plugin->getSettingsPage());
    }
}
