//
// Created by Hamlet on 2021/9/7.
//

#ifndef KMIND_KMPAINTWIDGET_H
#define KMIND_KMPAINTWIDGET_H

#include <QWidget>
#include "../core/kmNode.h"
#include "../painter/painter.h"

class kmPaintWidget : public QWidget {
Q_OBJECT

public:
    explicit kmPaintWidget(QWidget *parent = nullptr);
    ~kmPaintWidget() override;

    void createPainter(QWidget *content, kmNode *base_node);

private slots:
    void paintEvent(QPaintEvent *event) override;

private:
    Painter *m_painter = nullptr;
};


#endif //KMIND_KMPAINTWIDGET_H
