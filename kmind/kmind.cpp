//
// Created by Hamlet on 2021/9/6.
//

#include <QApplication>
#include "kmMainWindow.h"

QList<Shape *> Shape::ALL_SHAPE = QList<Shape *>();
QList<Skeleton *> Skeleton::ALL_SKELETON = QList<Skeleton *>();

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    kmMainWindow mainWindow;
    mainWindow.show();
    return QApplication::exec();
}
