//
// Created by Hamlet on 2021/9/7.
//

#ifndef KMIND_KMPAINTWIDGET_H
#define KMIND_KMPAINTWIDGET_H

#include <QWidget>
#include "kmNode.h"
#include <QTextEdit>
#include <QFontMetrics>
#include <QMainWindow>
#include <kmnodeedit.h>

class kmPaintWidget : public QWidget {
Q_OBJECT

public:
    explicit kmPaintWidget(QWidget *parent = nullptr);

    ~kmPaintWidget() override;

    void createPainter(QWidget *content, kmNode *base_node);

    void paint(QPainter *painter, QPaintEvent *event);

    void startEditingNode(kmNode *node);
    void finishEditingNode();

signals:

    void scrollBarPosNeedChange(int v, int h);

private slots:

    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

public slots:

    void setSelectedNode(kmNode *node);

    void node_newSubtopic();


    void editingNodeChange(kmNode *node);

    void node_newTopicAfter();

    void node_newTopicBefore();

    void node_moveLeft();

    void node_moveRight();

    void node_moveUp();

    void node_moveDown();

    void set_root(QMainWindow *wnd);

    void node_edit_finish();


private:
    QWidget *m_container;
    kmNode *m_baseNode;
    kmNode *m_selectedNode;
    kmNode *m_editingNode;

    QMainWindow *m_root;

    kmNodeEdit *m_textedit;
    bool m_NotFirstOpen = true;

    void paintAll(QPainter *painter, kmNode *start_node);
    void initNode(kmNode *node);
};


#endif //KMIND_KMPAINTWIDGET_H
