#include "clipboard.h"
#include <algorithm>

ClipboardModel::ClipboardModel(const size_t clipboardHistorySize,
                               const size_t pinnedClipboardHistorySize,
                               QObject *parent):
    QAbstractListModel {parent},
    m_clipboardHistorySize {clipboardHistorySize},
    m_pinnedClipboardHistorySize {pinnedClipboardHistorySize}
{
    m_clipboard.resize(defaultPinnedClipboardSize+m_clipboardHistorySize);
    m_pinned_clipboard.resize(0);
    _clipboard.resize(0);

    from_selected = false;
    clipboard = QGuiApplication::clipboard();

    clipboardChanged();

    connect(clipboard, &QClipboard::dataChanged,
            this, &ClipboardModel::clipboardChanged);

}

void ClipboardModel::clipboardChanged()
{
    if (!from_selected) {
        ClipboardItem item;

        if (_clipboard.size() > 0 && _clipboard.begin()->text == clipboard->text()) {
            return;
        }

        if (QString(clipboard->text()).isEmpty()) {
            item.text = "";
        }

        item.text = clipboard->text();
        item.pinned = false;
        item.selected = true;

        for (auto i = _clipboard.begin(); i != _clipboard.end(); ++i) {
            i->selected = false;
        }

        _clipboard.insert(_clipboard.begin(), item);

        m_clipboard.clear();
        m_clipboard.resize(defaultPinnedClipboardSize+m_clipboardHistorySize);
        m_clipboard.insert(m_clipboard.begin(), _clipboard.begin(), _clipboard.end());
        m_clipboard.insert(m_clipboard.begin(), m_pinned_clipboard.begin(), m_pinned_clipboard.end());

        emit dataChanged(createIndex(0,0),
             createIndex(m_pinnedClipboardHistorySize+m_clipboardHistorySize, 0));

    }
}

QHash<int, QByteArray> ClipboardModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ClipboardItemRoles::DisplayRole] = "display";
    roles[ClipboardItemRoles::TextColorRole] = "textcolor";

    return roles;
}


int ClipboardModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_clipboard.size();

}

QVariant ClipboardModel::data(const QModelIndex &index, int role) const
{

//    if (!index.isValid() || role != ClipboardItemRoles::DisplayRole || role != ClipboardItemRoles::TextColorRole) {
    if (!index.isValid() || index.row() > rowCount(index)) {
        return QVariant {};
    }

    const int rowIndex {index.row()};

    if (role == ClipboardItemRoles::DisplayRole) {
//        qDebug() << "display role : " << m_clipboard.at(rowIndex).text;
        return QVariant::fromValue(m_clipboard.at(rowIndex).text);
    }

    if (role == ClipboardItemRoles::TextColorRole) {

        QString color = "whitesmoke";

        if (m_clipboard.at(rowIndex).pinned) {
            color = "lightskyblue";
        }

//        qDebug() << "text color: " << color;

        return QVariant::fromValue(color);
    }

    return QVariant {};
}

size_t ClipboardModel::clipboardHistorySize() const
{
    return m_pinnedClipboardHistorySize+m_clipboardHistorySize;
}

bool ClipboardModel::selectItem(int index)
{
    from_selected = true;

    for (auto i = m_clipboard.begin(); i != m_clipboard.end(); ++i) {
        i->selected = false;
    }

    m_clipboard.at(index).selected = true;

    clipboard->setText(m_clipboard.at(index).text);

    from_selected = false;

    return !!index;
}

QString ClipboardModel::itemColor(int index) {
    QString color = "#323232";
    ClipboardItem item = m_clipboard.at(index);
    if (item.pinned == true) {
//        color = "#67686a";
    }

    if (item.selected == true) {
        //color = "steelblue";
    }

    //qDebug() << "Pinned: " << item.pinned << " Selected: " << item.selected << " Color: " << color;

    return color;
}

QString ClipboardModel::textColor(int index) {
    QString color = "white";
//    ClipboardItem item = m_clipboard.at(index);
//    if (item.pinned == true) {
//        color = "#0055ff";
//    }

    //qDebug() << "Pinned: " << item.pinned << " Selected: " << item.selected << " Color: " << color;

    return color;
}

bool ClipboardModel::pinItem(int index)
{
    ClipboardItem item = m_clipboard.at(index);
    ClipboardItem new_item;

    new_item.text = item.text;
    new_item.pinned = true;
    new_item.selected = false;

    if (QString(new_item.text).isEmpty()) {
        return false;
    }

    size_t pos = index - m_pinned_clipboard.size();

    if (_clipboard.size() > pos) {
        _clipboard.erase(_clipboard.begin()+pos);
    }
    else {
        return false;
    }

    m_pinned_clipboard.insert(m_pinned_clipboard.begin(), new_item);
    m_clipboard.clear();
    m_clipboard.resize(defaultPinnedClipboardSize+m_clipboardHistorySize);
    m_clipboard.insert(m_clipboard.begin(), _clipboard.begin(), _clipboard.end());
    m_clipboard.insert(m_clipboard.begin(), m_pinned_clipboard.begin(), m_pinned_clipboard.end());

    emit dataChanged(createIndex(0,0),
       createIndex(m_pinnedClipboardHistorySize+m_clipboardHistorySize, 0));

    return !!index;
}
