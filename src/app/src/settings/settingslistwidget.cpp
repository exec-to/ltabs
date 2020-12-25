#include "settingslistwidget.h"

SettingsListWidget::SettingsListWidget(QWidget* parent):
    QListView(parent) {

    this->setFixedWidth(200);
    this->setIconSize(QSize(32,32));
    this->setObjectName("settingsListWidget");
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
}
