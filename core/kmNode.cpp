//
// Created by Hamlet on 2021/9/6.
//

#include <QtWidgets/QApplication>
#include <QMouseEvent>
#include "kmNode.h"

inline QString defaultText(kmNodeType type) {
    switch (type) {
        case kmNodeType::BaseTopic:
            return QCoreApplication::translate("kmMainWindow", "Central Topic", nullptr);
        case kmNodeType::MainTopic:
            return QCoreApplication::translate("kmMainWindow", "Main Topic", nullptr);
        case kmNodeType::FloatTopic:
            return QCoreApplication::translate("kmMainWindow", "Floating Topic", nullptr);
        default:
            return QCoreApplication::translate("kmMainWindow", "Subtopic", nullptr);
    }
}

kmNode::kmNode(QWidget *parent, kmNode *parentNode, Skeleton *skeleton, int index, int level, kmNodeType type)
        : QWidget(parent), m_label(new QLabel(this)), m_parentNode(parentNode), m_skeleton(skeleton),
          m_index(index), m_level(level), m_type(type), m_style(Style::copy_style(skeleton->getStyle(type))) {
    m_parent = parent;

    QString text = defaultText(m_type);
    if (m_level > 1) {
        text.append(" ");
        text.append(QString::number(m_index));
    }
    m_label->setText(text);
    QRect need_rect = m_style.getShape()->getRect(m_label->size());
    this->setFixedWidth(need_rect.width());
    this->setFixedHeight(need_rect.height() + 100);
    m_label->move(need_rect.topLeft());

    this->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 170, 255)"));
}

kmNode::~kmNode() {
    for (const auto &node: m_children) {
        delete node;
    }
    delete m_label;
}

void kmNode::newSubtopic() {
    int level = m_level + 1;
    kmNodeType type;
    if (level == 2 && m_type == kmNodeType::BaseTopic)
        type = kmNodeType::MainTopic;
    else
        type = kmNodeType::SubTopic;
    auto *node = new kmNode(m_parent, this, m_skeleton, (int) m_children.size() + 1, level, type);
    m_children.append(node);
}

const QList<kmNode *> &kmNode::getChildren() const {
    return m_children;
}

const Style &kmNode::getStyle() const {
    return m_style;
}

void kmNode::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_lastMousePosition = event->globalPosition();
        qDebug() << "position set to " << m_lastMousePosition.x() << " " << m_lastMousePosition.y();
        emit scrollBarBeginMove();
    }
    event->ignore();
}

void kmNode::mouseMoveEvent(QMouseEvent *event) {
    if (m_type == kmNodeType::BaseTopic && event->buttons().testFlag(Qt::LeftButton)) {
        emit scrollBarPosUpdate(event->globalPosition().x() - m_lastMousePosition.x(),
                                event->globalPosition().y() - m_lastMousePosition.y());
    }
    event->ignore();
}

//void kmNode::mouseReleaseEvent(QMouseEvent *event) {
//    if (event->button() == Qt::LeftButton)
//        emit scrollBarEndMove();
//    event->ignore();
//}
