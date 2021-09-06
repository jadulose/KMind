//
// Created by Hamlet on 2021/9/6.
//

#include <QtWidgets/QApplication>
#include "kmNode.h"

inline QString defaultText(kmNodeType type) {
    switch (type) {
        case kmNodeType::BaseTopic:
            return QCoreApplication::translate("kmMainWindow", "Central Topic", nullptr);
        case kmNodeType::MainTopic:
            return QCoreApplication::translate("kmMainWindow", "Main Topic", nullptr);
        case kmNodeType::SubTopic:
            return QCoreApplication::translate("kmMainWindow", "Subtopic", nullptr);
        case kmNodeType::FloatTopic:
            return QCoreApplication::translate("kmMainWindow", "Floating Topic", nullptr);
    }
}

kmNode::kmNode(QWidget *parent, kmNode *parentNode, int index, int level, kmNodeType type)
        : QLabel(parent), m_parentNode(parentNode), m_index(index), m_level(level), m_type(type) {
    m_parent = parent;

    QString text = defaultText(m_type);
    if (m_level != 0) {
        text.append(" ");
        text.append(QString::number(m_index));
    }
    this->setText(text);
}

kmNode::~kmNode() {
    for (const auto &node: m_children)
        delete node;
}

void kmNode::newSubtopic() {
    int level = m_level + 1;
    kmNodeType type;
    if (level == 1 && m_type != kmNodeType::BaseTopic)
        type = kmNodeType::MainTopic;
    else
        type = kmNodeType::SubTopic;
    auto *node = new kmNode(m_parent, this, (int) m_children.size() + 1, level, type);
    m_children.append(node);
}
