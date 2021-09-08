//
// Created by Hamlet on 2021/9/6.
//

#ifndef KMIND_KMNODE_H
#define KMIND_KMNODE_H

#include <QLabel>
#include <QList>
#include "../painter/formwork.h"

class kmNode : public QLabel {
Q_OBJECT

public:
    explicit kmNode(QWidget *parent, kmNode *parentNode, Skeleton *skeleton, int index, int level, kmNodeType type);

    ~kmNode() override;

//    void newTopicAfter();

//    void newTopicBefore();

    void newSubtopic();

    const QList<kmNode *> &getChildren() const;

    const Style &getStyle() const;

private:
    kmNodeType m_type;
    int m_level;
    int m_index;
    Style m_style;

    QWidget *m_parent;
    kmNode *m_parentNode;
    Skeleton *m_skeleton;
    QList<kmNode *> m_children;
};


#endif //KMIND_KMNODE_H
