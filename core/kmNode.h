//
// Created by Hamlet on 2021/9/6.
//

#ifndef KMIND_KMNODE_H
#define KMIND_KMNODE_H

#include <QLabel>
#include <QList>

enum class kmNodeType {
    BaseTopic, MainTopic, SubTopic, FloatTopic
};

class kmNode : public QLabel {
Q_OBJECT

public:
    explicit kmNode(QWidget *parent = nullptr, kmNode *parentNode = nullptr,
           int index = 0, int level = 0, kmNodeType type = kmNodeType::SubTopic);

    ~kmNode() override;

    void newTopicAfter();

    void newTopicBefore();

    void newSubtopic();

private:
    kmNodeType m_type;
    int m_level;
    int m_index;

    QWidget *m_parent;
    kmNode *m_parentNode;
    QList<kmNode *> m_children;
};


#endif //KMIND_KMNODE_H
