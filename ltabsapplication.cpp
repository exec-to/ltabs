#include "ltabsapplication.h"

LTabsApplication::LTabsApplication(int &argc, char** argv):
    QApplication(argc, argv) {
}

LTabsApplication::~LTabsApplication() {

}

QUuid LTabsApplication::getUuid() {
    return QUuid("db507711-94ad-4f54-bffd-1a7789882839");
}
