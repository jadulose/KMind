//
// Created by Hamlet on 2021/9/6.
//

#include <QApplication>
#include "gui/kmMainWindow.h"

QList<Shape *> Shape::ALL_SHAPE = QList<Shape *>();
QList<Skeleton *> Skeleton::ALL_SKELETON = QList<Skeleton *>();

#include "node/k_arrange.h"

int main(int argc, char *argv[]) {
    //QApplication app(argc, argv);
    //kmMainWindow mainWindow;
    //mainWindow.show();
    k_arrange();
    return 0;//QApplication::exec();
}
