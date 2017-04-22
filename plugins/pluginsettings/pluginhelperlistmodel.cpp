#include "pluginhelperlistmodel.h"



PluginHelperListModel::PluginHelperListModel()
{
    load();

    connect(this, &PluginHelperListModel::applyChanges, this, &PluginHelperListModel::save);
    connect(this, &PluginHelperListModel::rejectChanges, this, &PluginHelperListModel::load);
}


QVariant PluginHelperListModel::data(const QModelIndex &index, int nRole) const {
    if (!index.isValid()) {
        return QVariant();
    }

    switch (nRole) {
        case Qt::DisplayRole: {
            return (m_list.at(index.row()).isActive) ? m_list.at(index.row()).fileName : QVariant();
        }
    }
    return QVariant();
}


QList<PluginHelper> PluginHelperListModel::getPlugins() const {
    return m_list;
}

//[add method]
void PluginHelperListModel::add(QString &filename) {
    if (filename.isEmpty() || filename.isNull())
        return;


    QPluginLoader loader(filename);
    QObject *pluginObject = loader.instance(); //todo: check erros
    IApplicationPlugin* plugin = qobject_cast<IApplicationPlugin*>(pluginObject);

    PluginHelper helper;
    helper.fileName = QFileInfo(filename).fileName(); //todo: only filename without path
    helper.uuid = plugin->getUuid();
    helper.isActive = true;
    int nrow = this->rowCount();
    if (this->insertRow(nrow)) {
        QModelIndex index = this->index(nrow);
        this->setData(index, QVariant::fromValue(helper));
    }
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
        helper->isActive = true;
        emit dataChanged(index,index);
        return true;
    }
    return false;
}


//[remove method]
void PluginHelperListModel::remove(QModelIndex &index) {
     /*if (!index.isValid())  {
         return;
     }
    this->removeRow(index.row());*/
}


void PluginHelperListModel::load() {
    QSettings settings;
    int size = settings.beginReadArray("EnabledPlugins");
    m_list.clear();
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        if (settings.value("isActive").toBool()) {
            PluginHelper plugin;
            plugin.uuid = QUuid(settings.value("uuid").toString());
            plugin.fileName = settings.value("fileName").toString();
            plugin.isActive = settings.value("isActive").toBool();
            m_list.append(plugin);
        }
    }
    settings.endArray();
}


void PluginHelperListModel::save() {
    QSettings settings;
    settings.beginWriteArray("EnabledPlugins");
    for (int i = 0; i < m_list.size(); ++i) {
        settings.setArrayIndex(i);
        settings.setValue("uuid", m_list.at(i).uuid.toString());
        settings.setValue("fileName", m_list.at(i).fileName);
        settings.setValue("isActive", m_list.at(i).isActive);
    }
    settings.endArray();
}


int PluginHelperListModel::rowCount(const QModelIndex &parent) const {
    return m_list.size();
}








