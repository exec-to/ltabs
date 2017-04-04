#include "settingslistwidget.h"

SettingsListWidget::SettingsListWidget(QWidget* parent):
    QListView(parent) {

    this->setFixedWidth(200);


   // connect(this->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),  )
}
