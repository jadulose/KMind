//
// Created by Hamlet on 2021/9/7.
//

#ifndef KMIND_PAINTER_H
#define KMIND_PAINTER_H

#include <QPainter>
#include "../core/kmNode.h"

class Painter {
public:
    explicit Painter(QWidget *container, QWidget *parent, kmNode *base_node);

    void paint(QPainter *painter, QPaintEvent *event);

private:
    QWidget *m_container;
    QWidget *m_parent;
    kmNode *m_baseNode;
};


#endif //KMIND_PAINTER_H
