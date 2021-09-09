//
// Created by Hamlet on 2021/9/6.
//

#ifndef KMIND_KMNODE_H
#define KMIND_KMNODE_H

#include <QLabel>
#include <QList>
#include "../painter/formwork.h"

class kmNode : public QWidget {
Q_OBJECT

public:
    explicit kmNode(QWidget *parent, kmNode *parentNode, Skeleton *skeleton, int index, int level, kmNodeType type);

    ~kmNode() override;

//    void newTopicAfter();

//    void newTopicBefore();

    void newSubtopic();

    [[nodiscard]] const QList<kmNode *> &getChildren() const;

    [[nodiscard]] const Style &getStyle() const;

signals:

    void scrollBarBeginMove();
    void scrollBarPosUpdate(double v, double h);

private slots:

    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

//    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    kmNodeType m_type;
    int m_level;
    int m_index;
    Style m_style;
    QLabel *m_label;

    QWidget *m_parent;
    kmNode *m_parentNode;
    Skeleton *m_skeleton;
    QList<kmNode *> m_children;

    QPointF m_lastMousePosition;
};


#endif //KMIND_KMNODE_H
