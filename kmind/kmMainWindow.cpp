//
// Created by Hamlet on 2021/9/6.
//

// You may need to build the project (run Qt uic code generator) to get "ui_kmMainWindow.h" resolved

#include "kmMainWindow.h"
#include "ui_kmMainWindow.h"
#include <QScrollBar>
#include <QKeyEvent>
#include <QDebug>

kmMainWindow::kmMainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::kmMainWindow) {
    ui->setupUi(this);
    ui->tabWidget->setVisible(false);
//    ui->scrollArea->horizontalScrollBar()->setFocusPolicy(Qt::NoFocus);
//    ui->scrollArea->verticalScrollBar()->setFocusPolicy(Qt::NoFocus);
//    this->installEventFilter(ui->scrollAreaWidgetContents);

//    读取，加载样式信息的代码暂时放在这
    auto shape = new Shape();
    Shape::ALL_SHAPE.append(shape);
    auto style1 = new Style(shape);
    auto style2 = new Style(shape);
    auto style3 = new Style(shape);
    auto style4 = new Style(shape);
    auto skeleton = new Skeleton(style1, style2, style3, style4);
    Skeleton::ALL_SKELETON.append(skeleton);

    m_baseNode = new kmNode(ui->scrollAreaWidgetContents, nullptr, skeleton, 1, 1, kmNodeType::BaseTopic);
    ui->scrollArea->setFocusPolicy(Qt::NoFocus);
    ui->scrollAreaWidgetContents->set_root(this);
    ui->scrollAreaWidgetContents->createPainter(ui->page, m_baseNode);
    ui->scrollArea->setAlignment(Qt::AlignCenter);

    connect(ui->actionMind_Map, SIGNAL(triggered(bool)), this, SLOT(displayMindMap()));
    connect(ui->actionOutliner, SIGNAL(triggered(bool)), this, SLOT(displayOutline()));
    connect(ui->scrollAreaWidgetContents, SIGNAL(scrollBarPosNeedChange(int, int)),
            this, SLOT(setScrollBarPos(int, int)));
    connect(ui->pushButton_Panel, SIGNAL(clicked(bool)), this, SLOT(switchPanel()));
    connect(m_baseNode, SIGNAL(scrollBarBeginMove()), this, SLOT(beginScrollBarMove()));
    connect(m_baseNode, SIGNAL(scrollBarPosUpdate(int, int)), this, SLOT(moveScrollBarPos(int, int)));

    connect(m_baseNode, SIGNAL(selectedNodeChange(kmNode * )), ui->scrollAreaWidgetContents,
            SLOT(setSelectedNode(kmNode * )));
    connect(ui->actionSubtopic, SIGNAL(triggered(bool)), ui->scrollAreaWidgetContents, SLOT(node_newSubtopic()));
    connect(ui->actionTopic_After, SIGNAL(triggered(bool)), ui->scrollAreaWidgetContents, SLOT(node_newTopicAfter()));
    connect(ui->actionTopic_Before, SIGNAL(triggered(bool)), ui->scrollAreaWidgetContents, SLOT(node_newTopicBefore()));
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
    bar1->setValue((bar1->maximum() - bar1->minimum()) * h / 10000);
    auto bar2 = ui->scrollArea->horizontalScrollBar();
    bar2->setValue((bar2->maximum() - bar2->minimum()) * v / 10000);
}

void kmMainWindow::moveScrollBarPos(int v, int h) {
    auto bar1 = ui->scrollArea->horizontalScrollBar();
    bar1->setValue(m_lastScrollBarPos.x() - (bar1->maximum() - bar1->minimum()) * v /
                                            (ui->scrollAreaWidgetContents->width() - ui->scrollArea->width()));
    auto bar2 = ui->scrollArea->verticalScrollBar();  // 为什么y方向移动偏差这么大
    bar2->setValue(m_lastScrollBarPos.y() - (bar2->maximum() - bar2->minimum()) * h /
                                            (ui->scrollAreaWidgetContents->height() - ui->scrollArea->height()));
}

void kmMainWindow::beginScrollBarMove() {
    m_lastScrollBarPos.setX(ui->scrollArea->horizontalScrollBar()->value());
    m_lastScrollBarPos.setY(ui->scrollArea->verticalScrollBar()->value());
}

void kmMainWindow::switchPanel() {
    ui->tabWidget->setVisible(!ui->tabWidget->isVisible());
}

void kmMainWindow::keyPressEvent(QKeyEvent *event) {
    qDebug() << "按键了" << event;
    switch (event->key()) {
        case Qt::Key_Tab:
            ui->scrollAreaWidgetContents->node_newSubtopic();
            break;
        case Qt::Key_Backspace:
        case Qt::Key_Delete:

            break;
        case Qt::Key_Left:
            ui->scrollAreaWidgetContents->node_moveLeft();
            break;
        case Qt::Key_Right:
            ui->scrollAreaWidgetContents->node_moveRight();
            break;
        case Qt::Key_Up:
            ui->scrollAreaWidgetContents->node_moveUp();
            break;
        case Qt::Key_Down:
            ui->scrollAreaWidgetContents->node_moveDown();
            break;
    }
    event->accept();
}

//void kmMainWindow::resizeEvent(QResizeEvent *event) {
//}
