//
// Created by Hamlet on 2021/9/7.
//

#include "kmPaintWidget.h"
#include <QStyleOption>
#include <QMouseEvent>

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

void kmPaintWidget::paint(QPainter *painter, QPaintEvent *event) {
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(Qt::darkGreen);

    // 第一步，排列所有的kmNode


    // 第二步，设置总体画布大小
    const auto &node_list = m_baseNode->getChildren();
    int width = 100;
    int height = 50 * node_list.size() + 50;
    this->setFixedWidth(width + m_container->width() * 2 - 100);
    this->setFixedHeight(height + m_container->height() * 2 - 100);

    // 第三步，移动所有kmNode并绘制
    int middle_x = this->width() / 2, middle_y = this->height() / 2;
    moveTo(m_baseNode, middle_x, middle_y);
    m_baseNode->getStyle().getShape()->paint(painter, m_baseNode);
    painter->setPen(Qt::blue);
    if (m_baseNode == m_selectedNode)
        painter->drawPath(ShapeElement::RoundRectangle::getPath(
                expandOutbound(m_baseNode->geometry())
        ));

    int w_sep = m_baseNode->width() / 2 + 50;
    int h_sep = 50;
    int start_x = middle_x + w_sep;
    int start_y;
    if (node_list.size() % 2 == 0) {
        start_y = middle_y + h_sep / 2 - node_list.size() / 2 * h_sep;
    } else {
        start_y = middle_y - node_list.size() / 2 * h_sep;
    }
    QPoint out_point =
            m_baseNode->geometry().topLeft() + m_baseNode->getStyle().getShape()->getOutPoint(m_baseNode->size());
    for (auto &node: node_list) {
        painter->setPen(Qt::darkGreen);
        moveLeftTo(node, start_x, start_y);
        start_y += h_sep;
        node->getStyle().getShape()->paint(painter, node);
        QPoint in_point = node->geometry().topLeft() + node->getStyle().getShape()->getInPoint(node->size());
        painter->drawLine(out_point.x(), out_point.y(), in_point.x(), in_point.y());
        painter->setPen(Qt::blue);
        if (node == m_selectedNode)
            painter->drawPath(ShapeElement::RoundRectangle::getPath(
                    expandOutbound(node->geometry())
            ));
    }
//    painter->drawLine(middle_x - 100, middle_y - 100, middle_x + 100, middle_y + 100);
}

void kmPaintWidget::mousePressEvent(QMouseEvent *event) {
    setSelectedNode(nullptr);
    event->ignore();
}
