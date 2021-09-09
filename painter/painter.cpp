//
// Created by Hamlet on 2021/9/7.
//

#include "painter.h"

Painter::Painter(QWidget *container, QWidget *parent, kmNode *base_node)
        : m_container(container), m_parent(parent), m_baseNode(base_node) {
}

inline void moveTo(QWidget *label, int x, int y) {
    label->move(x - label->width() / 2, y - label->height() / 2);
}

inline void moveLeftTo(QWidget *label, int x, int y) {
    label->move(x, y - label->height() / 2);
}

void Painter::paint(QPainter *painter, QPaintEvent *event) {
    const auto &node_list = m_baseNode->getChildren();
    int width = 100;
    int height = 50 * node_list.size() + 50;
    m_parent->setFixedWidth(width + m_container->width() * 2 - 100);
    m_parent->setFixedHeight(height + m_container->height() * 2 - 100);

    int middle_x = m_parent->width() / 2, middle_y = m_parent->height() / 2;
    moveTo(m_baseNode, middle_x, middle_y);
    int w_sep = m_baseNode->width() / 2 + 50;
    int h_sep = 50;
    int start_x = middle_x + w_sep;
    int start_y;
    if (node_list.size() % 2 == 0) {
        start_y = middle_y + h_sep / 2 - node_list.size() / 2 * h_sep;
    } else {
        start_y = middle_y - node_list.size() / 2 * h_sep;
    }
    for (auto &node: node_list) {
        moveLeftTo(node, start_x, start_y);
        start_y += h_sep;
    }
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(Qt::darkGreen);
    painter->drawLine(middle_x - 100, middle_y - 100, middle_x + 100, middle_y + 100);
//    Shape shape;
//    shape.paint(painter, m_baseNode);
}
