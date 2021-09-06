//
// Created by Hamlet on 2021/9/6.
//

#include <QApplication>
#include "gui/kmMainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    kmMainWindow mainWindow;
    mainWindow.show();
    return QApplication::exec();
}
