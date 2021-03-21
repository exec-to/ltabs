#include "clipboard.h"
#include <algorithm>

ClipboardModel::ClipboardModel(const size_t clipboardHistorySize, QObject *parent):
    QAbstractListModel {parent},
    m_clipboardHistorySize {clipboardHistorySize}
{
    m_clipboard.resize(m_clipboardHistorySize);
    ClipboardItem i1, i2;
    i1.text = "Hello 1";
    i2.text = "Hello 2";
    m_clipboard.push_back(i1);
    m_clipboard.push_back(i2);
}

int ClipboardModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_clipboard.size();

}

QVariant ClipboardModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant {};
    }

    const int rowIndex {index.row()};
    return QVariant::fromValue(m_clipboard.at(rowIndex).text);

}

size_t ClipboardModel::clipboardHistorySize() const
{
    return m_clipboardHistorySize;
}

bool ClipboardModel::selectItem(int index)
{

    m_clipboard.at(index).text = QString::number(index);
//    set to clipboard
    // will be replaced to emit rowUpdated ?
    emit dataChanged(createIndex(0,0), createIndex(m_clipboardHistorySize, 0));
    return !!index;
}