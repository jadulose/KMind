//
// Created by Hamlet on 2021/9/7.
//

#ifndef KMIND_STYLEUTIL_H
#define KMIND_STYLEUTIL_H

#include <QPainter>
#include <QRect>
#include "../core/kmNode.h"

enum class State {
    VeryImportant, Important, CrossOut, Default
};

enum class LineWidth {
    XS, S, M, L, XL
};

class Shape {
public:
    explicit Shape(double x_ratio=12, double y_ratio=10, double w_ratio=12, double h_ratio=10,
                   double inP_x_ratio=0, double inP_y_ratio=0.5, double outP_x_ratio=1, double outP_y_ratio=0.5);

    QRect getRect(const QSize &content_size);

    QPoint getInPoint(const QSize &outer_size);

    QPoint getOutPoint(const QSize &outer_size);

    void paint(QPainter *painter, QLabel *label);

private:
    double x_ratio, y_ratio, w_ratio, h_ratio;
    double inP_x_ratio, inP_y_ratio, outP_x_ratio, outP_y_ratio;

    QColor m_fillColor;
    QColor m_borderColor;
    LineWidth m_borderWidth = LineWidth::S;
    int m_width;
};

class Font;

class Structure;

class Branch;

#endif //KMIND_STYLEUTIL_H
