//
// Created by Hamlet on 2021/9/7.
//

#include "kmPaintWidget.h"
#include <QStyleOption>
#include <QMouseEvent>
#include <QDebug>

kmPaintWidget::kmPaintWidget(QWidget *parent) : QWidget(parent) {
    this->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255)"));
}

kmPaintWidget::~kmPaintWidget() {
}

void kmPaintWidget::createPainter(QWidget *content, kmNode *base_node) {
    m_container = content;
    m_baseNode = base_node;
    m_selectedNode = base_node;
}

void kmPaintWidget::paintEvent(QPaintEvent *event) {
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    this->style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    paint(&painter, event);
    if (m_NotFirstOpen) {
        emit scrollBarPosNeedChange(5000, 5000);
        m_NotFirstOpen = false;
    }
}

void kmPaintWidget::setSelectedNode(kmNode *node) {
    m_selectedNode = node;
    this->repaint();
}

inline void moveTo(QWidget *label, int x, int y) {
    label->move(x - label->width() / 2, y - label->height() / 2);
}

inline void moveLeftTo(QWidget *label, int x, int y) {
    label->move(x, y - label->height() / 2);
}

QRect expandOutbound(const QRect &rect) {
    QRect rec_o = rect;
    rec_o.setX(rec_o.x() - 3), rec_o.setY(rec_o.y() - 3);
    rec_o.setWidth(rec_o.width() + 6), rec_o.setHeight(rec_o.height() + 6);
    return rec_o;
}

inline void tempMove(kmNode *node, const QPoint &point) {  // 只移动自己
    node->m_tempPos += point;
}

inline void tempMoveAll(kmNode *node, const QPoint &point) {
    node->m_tempPos += point;
    // 需要遍历字节点并移动
    for (const auto &child: node->getChildren())
        tempMoveAll(child, point);
}

inline void tempMoveTo(kmNode *node, const QPoint &point) {  // 全体移动
    tempMoveAll(node, point - node->m_tempPos);
}

inline void acceptTempPos(kmNode *node) {
    node->acceptTempPos();
    for (const auto &child: node->getChildren())
        acceptTempPos(child);
}

QPoint rearrageNodes(kmNode *start_node) {  // TODO 到底排列的点是位于中间还是左上角
    const auto &children = start_node->getChildren();
    if (children.empty())
        return {0, 60};
    else if (children.size() == 1) {
        const auto &node = children.at(0);
        const auto &center = start_node->geometry().center();
        tempMoveTo(node, {center.x() + start_node->width() / 2 + 50, center.y()});
        QPoint p = rearrageNodes(node);
        tempMove(node, {0, p.x()});
        return {p.x(), p.y()};
    } else {
        bool is_begin_x = true;
        int begin_x;
        QPoint center = start_node->geometry().center() + QPoint(start_node->width() / 2 + 50, 0);
        QPoint p;
        for (const auto &child: children) {
            tempMoveTo(child, center);
            p = rearrageNodes(child);
            tempMove(child, {0, p.x()});
            center += {0, p.y()};
            if (is_begin_x) {
                begin_x = p.x();
                is_begin_x = false;
            }
        }
        int sep = children.last()->m_tempPos.y() - children.first()->m_tempPos.y();
        return {begin_x + sep / 2, begin_x + sep + p.y() - p.x()};
    }
}

void kmPaintWidget::paintAll(QPainter *painter, kmNode *start_node) {
    painter->setPen(Qt::darkGreen);
    start_node->getStyle().getShape()->paint(painter, start_node);
    painter->setPen(Qt::blue);
    if (start_node == m_selectedNode)
        painter->drawPath(ShapeElement::RoundRectangle::getPath(expandOutbound(start_node->geometry())));
    QPoint out_point =
            start_node->geometry().topLeft() + start_node->getStyle().getShape()->getOutPoint(start_node->size());
    for (const auto &node: start_node->getChildren()) {
        painter->setPen(Qt::darkGreen);
        QPoint in_point = node->geometry().topLeft() + node->getStyle().getShape()->getInPoint(node->size());
        painter->drawLine(out_point.x(), out_point.y(), in_point.x(), in_point.y());
        paintAll(painter, node);
    }
}

void kmPaintWidget::paint(QPainter *painter, QPaintEvent *event) {
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(Qt::darkGreen);

    // 第一步，排列所有的kmNode
    QPoint p = rearrageNodes(m_baseNode);
    tempMove(m_baseNode, {0, p.x()});

    // 第二步，设置总体画布大小
    const auto &node_list = m_baseNode->getChildren();
    int width = 100;
    int height = 50 * node_list.size() + 50;
    this->setFixedWidth(width + m_container->width() * 2 - 100);
    this->setFixedHeight(height + m_container->height() * 2 - 100);

    // 第三步，移动所有kmNode
    int middle_x = this->width() / 2, middle_y = this->height() / 2;
    tempMoveTo(m_baseNode, {middle_x, middle_y});
    acceptTempPos(m_baseNode);

    // 第四步，绘制
    paintAll(painter, m_baseNode);
}

void kmPaintWidget::mousePressEvent(QMouseEvent *event) {
    setSelectedNode(nullptr);
    event->ignore();
}

void kmPaintWidget::node_newSubtopic() {
    if (m_selectedNode == nullptr)
        return;
    auto *node = m_selectedNode->newSubtopic();
    node->show();
    connect(node, SIGNAL(selectedNodeChange(kmNode*)), this, SLOT(setSelectedNode(kmNode*)));
    this->repaint();
}
