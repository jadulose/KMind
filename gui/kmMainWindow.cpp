//
// Created by Hamlet on 2021/9/6.
//

// You may need to build the project (run Qt uic code generator) to get "ui_kmMainWindow.h" resolved

#include "kmMainWindow.h"
#include "ui_kmMainWindow.h"


kmMainWindow::kmMainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::kmMainWindow) {
    ui->setupUi(this);
    m_baseNode = new kmNode(ui->scrollAreaWidgetContents, nullptr, 1, 1, kmNodeType::BaseTopic);
    m_selectedNode = m_baseNode;
    m_baseNode->newSubtopic();
    m_baseNode->newSubtopic();
    m_baseNode->newSubtopic();
    ui->scrollAreaWidgetContents->createPainter(ui->page, m_baseNode);
    ui->scrollArea->setAlignment(Qt::AlignCenter);

    connect(ui->actionMind_Map, SIGNAL(triggered(bool)), this, SLOT(displayMindMap()));
    connect(ui->actionOutliner, SIGNAL(triggered(bool)), this, SLOT(displayOutline()));
}

kmMainWindow::~kmMainWindow() {
    delete m_baseNode;
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

void kmMainWindow::resizeEvent(QResizeEvent *event) {
//    m_painter->paint();
}
