#ifndef CLIPBOARD_H
#define CLIPBOARD_H
#include <QAbstractListModel>
#include <vector>
#include <QClipboard>
#include <QObject>
#include <QtWidgets>

struct ClipboardItem {
    QString text;
};

class ClipboardModel: public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int historySize READ clipboardHistorySize CONSTANT)
    // use it in QML root.model.historySize

public:
    static constexpr size_t defaultClipboardHistorySize {20};
    static constexpr size_t defaultPinnedClipboardSize {5};
    ClipboardModel(const size_t clipboardHistorySize = defaultClipboardHistorySize,
                   QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex {}) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void clipboardChanged();

    size_t clipboardHistorySize() const;

    Q_INVOKABLE bool selectItem(int index);
    Q_INVOKABLE bool PinItem(int index);

private:
    QClipboard *clipboard;
    std::vector<ClipboardItem> m_clipboard;
    std::vector<ClipboardItem> m_pinned_clipboard;
    const size_t m_clipboardHistorySize;
    bool from_selected;
};

Q_DECLARE_METATYPE(ClipboardItem);

#endif // CLIPBOARD_H
