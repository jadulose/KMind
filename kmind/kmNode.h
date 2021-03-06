//
// Created by Hamlet on 2021/9/6.
//

#ifndef KMIND_KMNODE_H
#define KMIND_KMNODE_H

#include <QLabel>
#include <QList>
#include "formwork.h"

class kmNode : public QWidget {
Q_OBJECT

public:
    explicit kmNode(QWidget *parent, kmNode *parentNode, Skeleton *skeleton, int index, int level, kmNodeType type);

    ~kmNode() override;

    kmNode *newTopicAfter();

    kmNode *newTopicBefore();

    kmNode *newSubtopic();

    [[nodiscard]] const QList<kmNode *> &getChildren() const;

    [[nodiscard]] const Style &getStyle() const;

    [[nodiscard]] kmNode *getFatherNode() const { return m_parentNode; }

    void setPreferredSize();

    QString text();
    void setText(QString t);

//    [[nodiscard]] const QLabel *getLabel() const { return m_label; }

signals:

    void scrollBarBeginMove();

    void scrollBarPosUpdate(int v, int h);

    void selectedNodeChange(kmNode *node);

    void editingNodeChange(kmNode *node);

private slots:

    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseDoubleClickEvent(QMouseEvent *event) override;

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
    QList<kmNode *> m_children;  // 考虑换成链表吧

    QPoint m_lastMousePosition;

public:
    QPoint m_tempPos;

    void acceptTempPos();
};


#endif //KMIND_KMNODE_H
