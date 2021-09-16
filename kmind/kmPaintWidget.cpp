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
    delete m_textedit;
}

void kmPaintWidget::createPainter(QWidget *content, kmNode *base_node) {
    m_container = content;
    m_baseNode = base_node;
    m_selectedNode = base_node;
    m_editingNode = nullptr;
    m_textedit = new kmNodeEdit(this);
    connect(m_textedit,SIGNAL(finish()),this,SLOT(node_edit_finish()));
    m_textedit->hide();
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

//inline void moveTo(QWidget *label, int x, int y) {
//    label->move(x - label->width() / 2, y - label->height() / 2);
//}
//
//inline void moveLeftTo(QWidget *label, int x, int y) {
//    label->move(x, y - label->height() / 2);
//}

inline QRect expandOutbound(const QRect &rect) {
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
        return {30, 60};
    else if (children.size() == 1) {
        const auto &node = children.at(0);
        const auto &center = start_node->geometry().center();
        QPoint p = rearrageNodes(node);
        tempMove(node, {0, p.x()});
        tempMoveTo(node, {center.x() + start_node->width() / 2 + 50, center.y()});
        return {p.x(), p.y()};
    } else {
        bool is_begin_x = true;
        int begin_x;
        QPoint center = start_node->geometry().center() + QPoint(start_node->width() / 2 + 50, 0);
        QPoint p;
        for (const auto &child: children) {
            p = rearrageNodes(child);
            tempMove(child, {0, p.x()});
            tempMoveTo(child, center + QPoint{0, p.x()});
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

    //this->setFocus();
}

void kmPaintWidget::mousePressEvent(QMouseEvent *event) {
    finishEditingNode();
    setSelectedNode(nullptr);
    event->ignore();
}

void kmPaintWidget::node_newSubtopic() {
    if (m_selectedNode == nullptr)
        return;
    initNode(m_selectedNode->newSubtopic());
}

void kmPaintWidget::node_newTopicAfter() {
    if (m_selectedNode == nullptr)
        return;
    if (m_selectedNode == m_baseNode) {
        node_newSubtopic();
        return;
    }
    initNode(m_selectedNode->newTopicAfter());
}

void kmPaintWidget::node_newTopicBefore() {
    if (m_selectedNode == nullptr)
        return;
    if (m_selectedNode == m_baseNode) {
        node_newSubtopic();
        return;
    }
    initNode(m_selectedNode->newTopicBefore());
}

void kmPaintWidget::initNode(kmNode *node) {
    connect(node, SIGNAL(selectedNodeChange(kmNode * )), this, SLOT(setSelectedNode(kmNode * )));
    node->show();

    connect(node, SIGNAL(selectedNodeChange(kmNode*)), this, SLOT(setSelectedNode(kmNode*)));
    connect(node, SIGNAL(editingNodeChange(kmNode*)), this, SLOT(editingNodeChange(kmNode*)));
    this->repaint();

    startEditingNode(node);

    setSelectedNode(node);
}

void kmPaintWidget::node_moveLeft() {
    if(!m_selectedNode)
        return;
    if (m_selectedNode == m_baseNode)
        return;
    setSelectedNode(m_selectedNode->getFatherNode());
}

void kmPaintWidget::node_moveRight() {
    if(!m_selectedNode)
        return;
    if (m_selectedNode->getChildren().empty())
        return;
    setSelectedNode(m_selectedNode->getChildren().at(m_selectedNode->getChildren().size() / 2));
}

void kmPaintWidget::node_moveUp() {
    if (m_selectedNode == m_baseNode)
        return;
    int index = m_selectedNode->getFatherNode()->getChildren().indexOf(m_selectedNode);
    setSelectedNode(m_selectedNode->getFatherNode()->getChildren().at(index > 0 ? index - 1 : 0));
}

void kmPaintWidget::node_moveDown() {
    if (m_selectedNode == m_baseNode)
        return;
    const auto &children = m_selectedNode->getFatherNode()->getChildren();
    int index = children.indexOf(m_selectedNode) + 1;
    setSelectedNode(children.at(index < children.size() ? index : index - 1));

}

void kmPaintWidget::set_root(QMainWindow *wnd)
{
    this->m_root = wnd;
}

void kmPaintWidget::editingNodeChange(kmNode *node)
{
    startEditingNode(node);
}

void kmPaintWidget::startEditingNode(kmNode *node)
{
    m_editingNode = node;
    m_textedit->setText(node->text());
    m_textedit->selectAll();

    if(m_textedit->isHidden())
    {
        m_textedit->setWindowFlag(Qt::Widget);
        m_textedit->show();
    }
        m_textedit->move(node->pos());
        m_textedit->resize(node->size());
        m_textedit->show();
        m_textedit->setFocus();
        m_textedit->raise();
}

void kmPaintWidget::finishEditingNode()
{
    if(!m_textedit->isHidden()){
        m_editingNode->setText(m_textedit->toPlainText());
        m_textedit->hide();
        QFontMetrics qfm(m_editingNode->font());
        m_editingNode->setFixedWidth(20+qfm.horizontalAdvance(m_textedit->toPlainText()));
    }
    m_root->setFocus();
    repaint();
}

void kmPaintWidget::node_edit_finish()
{
    finishEditingNode();
}
