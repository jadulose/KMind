//
// Created by Hamlet on 2021/9/7.
//

#ifndef KMIND_KMPAINTWIDGET_H
#define KMIND_KMPAINTWIDGET_H

#include <QWidget>
#include "kmNode.h"

class kmPaintWidget : public QWidget {
Q_OBJECT

public:
    explicit kmPaintWidget(QWidget *parent = nullptr);

    ~kmPaintWidget() override;

    void createPainter(QWidget *content, kmNode *base_node);

    void paint(QPainter *painter, QPaintEvent *event);

signals:

    void scrollBarPosNeedChange(int v, int h);

private slots:

    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

public slots:

    void setSelectedNode(kmNode *node);

    void node_newSubtopic();

private:
    QWidget *m_container;
    kmNode *m_baseNode;
    kmNode *m_selectedNode;
    bool m_NotFirstOpen = true;

    void paintAll(QPainter *painter, kmNode *start_node);
};


#endif //KMIND_KMPAINTWIDGET_H
