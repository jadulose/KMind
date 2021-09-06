//
// Created by Hamlet on 2021/9/6.
//

// You may need to build the project (run Qt uic code generator) to get "ui_kmMainWindow.h" resolved

#include "kmMainWindow.h"
#include "ui_kmMainWindow.h"


kmMainWindow::kmMainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::kmMainWindow) {
    ui->setupUi(this);

    connect(ui->actionMind_Map, SIGNAL(triggered(bool)), this, SLOT(displayMindMap()));
    connect(ui->actionOutliner, SIGNAL(triggered(bool)), this, SLOT(displayOutline()));
}

kmMainWindow::~kmMainWindow() {
    delete ui;
}

void kmMainWindow::displayMindMap() {
    ui->actionMind_Map->setChecked(true);
    ui->actionOutliner->setChecked(false);
}

void kmMainWindow::displayOutline() {
    ui->actionMind_Map->setChecked(false);
    ui->actionOutliner->setChecked(true);
}
