#ifndef CLIPBOARD_H
#define CLIPBOARD_H
#include <QAbstractListModel>
#include <vector>
#include <QClipboard>
#include <QObject>
#include <QtWidgets>

struct ClipboardItem {
    QString text;
    bool pinned;
    bool selected;
};

class ClipboardModel: public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int historySize READ clipboardHistorySize CONSTANT)
    // use it in QML root.model.historySize

public:
// TODO: Limit clipboard size
    static constexpr size_t defaultClipboardHistorySize {20};
    static constexpr size_t defaultPinnedClipboardSize {5};
    ClipboardModel(const size_t clipboardHistorySize = defaultClipboardHistorySize,
                   const size_t pinnedClipboardHistorySize = defaultPinnedClipboardSize,
                   QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex {}) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void clipboardChanged();

    QHash<int,QByteArray> roleNames() const override;

    size_t clipboardHistorySize() const;

    Q_INVOKABLE bool selectItem(int index);
    Q_INVOKABLE bool pinItem(int index);
    Q_INVOKABLE QString itemColor(int index);
    Q_INVOKABLE QString textColor(int index);

private:
    QClipboard *clipboard;
    std::vector<ClipboardItem> m_clipboard;
    std::vector<ClipboardItem> m_pinned_clipboard;
    std::vector<ClipboardItem> _clipboard;
    const size_t m_clipboardHistorySize;
    const size_t m_pinnedClipboardHistorySize;
    bool from_selected;

    enum ClipboardItemRoles {
        DisplayRole = Qt::UserRole + 1,
        TextColorRole
    };

};

Q_DECLARE_METATYPE(ClipboardItem);

#endif // CLIPBOARD_H
