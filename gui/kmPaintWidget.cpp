//
// Created by Hamlet on 2021/9/7.
//

#include <QStyleOption>
#include "kmPaintWidget.h"

kmPaintWidget::kmPaintWidget(QWidget *parent) : QWidget(parent) {
    this->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255)"));
}

kmPaintWidget::~kmPaintWidget() {
    if (m_painter != nullptr)
        delete m_painter;
}

void kmPaintWidget::createPainter(QWidget *content, kmNode *base_node) {
    if (m_painter == nullptr)
        m_painter = new Painter(content, this, base_node);
}

void kmPaintWidget::paintEvent(QPaintEvent *event) {
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    this->style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    m_painter->paint(&painter, event);
    if (m_NotFirstOpen) {
        emit scrollBarPosNeedChange(50, 50);
        m_NotFirstOpen = false;
    }
}
