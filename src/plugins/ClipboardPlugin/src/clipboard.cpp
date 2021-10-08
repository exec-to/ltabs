#include "clipboard.h"
#include <algorithm>

ClipboardModel::ClipboardModel(const size_t clipboardHistorySize, QObject *parent):
    QAbstractListModel {parent},
    m_clipboardHistorySize {clipboardHistorySize}
{
    m_clipboard.resize(m_clipboardHistorySize);
    m_pinned_clipboard.resize(defaultPinnedClipboardSize);

    from_selected = false;
    clipboard = QGuiApplication::clipboard();

    connect(clipboard, &QClipboard::dataChanged,
            this, &ClipboardModel::clipboardChanged);

}

void ClipboardModel::clipboardChanged()
{
    if (!from_selected) {
        ClipboardItem item;

        if (m_clipboard.begin()->text == clipboard->text()) {
            return;
        }


        item.text = clipboard->text();

        if (QString(item.text).isEmpty()) {
            return;
        }

        m_clipboard.insert(m_clipboard.begin(), item);

        emit dataChanged(createIndex(0,0),
             createIndex(m_clipboardHistorySize, 0));
    }
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

//    m_clipboard.at(index).text = QString::number(index);
      from_selected = true;
      clipboard->setText(m_clipboard.at(index).text);
      from_selected = false;
//    set to clipboard
    // will be replaced to emit rowUpdated ?
//    emit dataChanged(createIndex(0,0), createIndex(m_clipboardHistorySize, 0));
    return !!index;
}



bool ClipboardModel::pinItem(int index)
{
          ClipboardItem item = m_clipboard.at(index);
          ClipboardItem new_item;

          new_item.text = item->text();

          if (QString(new_item.text).isEmpty()) {
              return;
          }

          m_pinned_clipboard.insert(m_pinned_clipboard.begin(), item);

          //vector delete, возможно нужно хранить индекс в ClipboardItem
          m_clipboard.erase(item);

          emit dataChanged(createIndex(0,0),
               createIndex(m_clipboardHistorySize, 0));
//    set to clipboard
    // will be replaced to emit rowUpdated ?
//    emit dataChanged(createIndex(0,0), createIndex(m_clipboardHistorySize, 0));
    return !!index;
}
