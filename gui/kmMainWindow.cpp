//
// Created by Hamlet on 2021/9/6.
//

// You may need to build the project (run Qt uic code generator) to get "ui_kmMainWindow.h" resolved

#include "kmMainWindow.h"
#include "ui_kmMainWindow.h"
#include <QScrollBar>

kmMainWindow::kmMainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::kmMainWindow) {
    ui->setupUi(this);

//    读取，加载样式信息的代码暂时放在这
    auto shape = new Shape();
    Shape::ALL_SHAPE.append(shape);
    auto style1 = new Style();
    auto style2 = new Style();
    auto style3 = new Style();
    auto style4 = new Style();
    auto skeleton = new Skeleton(style1, style2, style3, style4);
    Skeleton::ALL_SKELETON.append(skeleton);

    m_baseNode = new kmNode(ui->scrollAreaWidgetContents, nullptr, skeleton, 1, 1, kmNodeType::BaseTopic);
    m_selectedNode = m_baseNode;
    m_baseNode->newSubtopic();
    m_baseNode->newSubtopic();
    m_baseNode->newSubtopic();
    ui->scrollAreaWidgetContents->createPainter(ui->page, m_baseNode);
    ui->scrollArea->setAlignment(Qt::AlignCenter);

    connect(ui->actionMind_Map, SIGNAL(triggered(bool)), this, SLOT(displayMindMap()));
    connect(ui->actionOutliner, SIGNAL(triggered(bool)), this, SLOT(displayOutline()));
    connect(ui->scrollAreaWidgetContents, SIGNAL(scrollBarPosNeedChange(int,int)),
            this, SLOT(setScrollBarPos(int,int)));
}

kmMainWindow::~kmMainWindow() {
    delete m_baseNode;
    delete ui;
//    暂时在这里对静态成员进行处理
    for (const auto &shape: Shape::ALL_SHAPE)
        delete shape;
    for (const auto &skeleton: Skeleton::ALL_SKELETON)
        delete skeleton;
}

void kmMainWindow::displayMindMap() {
    ui->actionMind_Map->setChecked(true);
    ui->actionOutliner->setChecked(false);
}

void kmMainWindow::displayOutline() {
    ui->actionMind_Map->setChecked(false);
    ui->actionOutliner->setChecked(true);
}

void kmMainWindow::setScrollBarPos(int v, int h) {
    auto bar1 = ui->scrollArea->verticalScrollBar();
    bar1->setValue((bar1->maximum() - bar1->minimum()) * v / 100);
    auto bar2 = ui->scrollArea->horizontalScrollBar();
    bar2->setValue((bar2->maximum() - bar2->minimum()) * h / 100);
}

//void kmMainWindow::resizeEvent(QResizeEvent *event) {
//    auto bar1 = ui->scrollArea->verticalScrollBar();
//    bar1->setValue((bar1->maximum() - bar1->minimum()) / 2);
//    auto bar2 = ui->scrollArea->horizontalScrollBar();
//    bar2->setValue((bar2->maximum() - bar2->minimum()) / 2);
//}
