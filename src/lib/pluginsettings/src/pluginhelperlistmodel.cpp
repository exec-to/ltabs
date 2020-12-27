/*
Setting page for manage plugins
*/

#include "pluginhelperlistmodel.h"



PluginHelperListModel::PluginHelperListModel()
{
    load();
    connect(this, &PluginHelperListModel::dataChanged, this, &PluginHelperListModel::save);
}


QVariant PluginHelperListModel::data(const QModelIndex &index, int nRole) const {
    if (!index.isValid()) {
        return QVariant();
    }

    switch (nRole) {
        case Qt::DisplayRole: {
            return m_list.at(index.row()).fileName;
        }
    }
    return QVariant();
}

//[add method]
void PluginHelperListModel::add(QString &filename) {
    if (filename.isNull() || filename.isEmpty()) {
        return;
    }

    if (!QFileInfo(filename).exists()) {
        QMessageBox::critical(0,"Error", "file does not exist");
        return;
    }

    QPluginLoader loader(filename);
    QObject *pluginObject = loader.instance();

    if (!pluginObject) {
        QMessageBox::critical(0,"Error", "unknown plugin format");
        return;
    }

    IApplicationPlugin* plugin = qobject_cast<IApplicationPlugin*>(pluginObject);

    if (!plugin) {
        QMessageBox::critical(0,"Unknown Error", "can't add plugin");
        return;
    }

    PluginHelper helper(plugin->getUuid().toString(), QFileInfo(filename).fileName());

    if (m_list.contains(helper)) {
        QMessageBox::critical(0,"Error", "plugin are exist");
        return;
    }

    int nrow = this->rowCount();
    if (this->insertRow(nrow)) {
        QModelIndex index = createIndex(nrow,0);//this->index(nrow);
        this->setData(index, QVariant::fromValue(helper));
    }

    loader.unload();
}

//[remove method]
void PluginHelperListModel::remove(QModelIndex &index) {

    if (!index.isValid()) {
        return;
    }

    this->removeRow(index.row());
    emit dataChanged(index,index);
}


void PluginHelperListModel::moveUp(QModelIndex &index) {
    if (!index.isValid() || index.row() == 0) {
        return;
    }
    moveRows(QModelIndex(),index.row(),1,QModelIndex(),index.row()-1);
    emit dataChanged(index,index);
}


void PluginHelperListModel::moveDown(QModelIndex &index) {
    if (!index.isValid() || index.row() == m_list.size()-1) {
        return;
    }
    QModelIndex next_index = this->index(index.row() + 1);
    moveUp(next_index);
}


bool PluginHelperListModel::moveRows(const QModelIndex &sourceParent, int sourceRow, int count,
                      const QModelIndex &destinationParent, int destinationChild)
{
    if (beginMoveRows(sourceParent,sourceRow,count,destinationParent,destinationChild)) {
        m_list.swap(sourceRow,destinationChild);
        endMoveRows();
        return true;
    }
    return false;
}


bool PluginHelperListModel::removeRows(int row, int count, const QModelIndex &parent) {
    beginRemoveRows(parent,row, row+count - 1);
    m_list.removeAt(row);
    endRemoveRows();
    return true;
}


bool PluginHelperListModel::insertRows(int row, int count, const QModelIndex &parent) {
    beginInsertRows(parent,row, row+count - 1);
    m_list.append(PluginHelper());
    endInsertRows();
    return true;
}


bool PluginHelperListModel::setData(const QModelIndex &index, const QVariant &value, int role) {

    if (index.isValid() && role == Qt::EditRole)  {
        PluginHelper *helper = &m_list[index.row()];
        helper->fileName = value.value<PluginHelper>().fileName;
        helper->uuid = value.value<PluginHelper>().uuid;
        emit dataChanged(index,index);
        return true;
    }
    return false;
}


void PluginHelperListModel::load() {
    int size = configuration::master()->beginReadArray(configuration::Plugins());
    m_list.clear();
    for (int i = 0; i < size; ++i) {
        configuration::master()->setArrayIndex(i);
        m_list.append(PluginHelper(configuration::Plugins::uuid(), configuration::Plugins::file_name()));
    }
    configuration::master()->endArray();
}


void PluginHelperListModel::save() {
    configuration::master()->remove(configuration::Plugins());
    configuration::master()->beginWriteArray(configuration::Plugins());
    for (int i = 0; i < m_list.size(); ++i) {
        configuration::master()->setArrayIndex(i);
        configuration::Plugins::uuid(m_list.at(i).uuid.toString());
        configuration::Plugins::file_name(m_list.at(i).fileName);
    }
    configuration::master()->endArray();
    configuration::master()->sync();
}


int PluginHelperListModel::rowCount(const QModelIndex &parent) const {
    return m_list.size();
}
