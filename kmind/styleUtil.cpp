//
// Created by Hamlet on 2021/9/7.
//

#include <QPainterPath>
#include "styleUtil.h"

// 注意：边界的距离并不是倍数关系，有的是固定长度，有的则是其他形式

QRect Shape::getRect(const QSize &content_size) const {
    int w = content_size.width(), h = content_size.height();
    return QRect(x_ratio, y_ratio, 2 * w_ratio + w, 2 * h_ratio + h);
}

QPoint Shape::getInPoint(const QSize &outer_size) {
    return QPoint(outer_size.width() * inP_x_ratio, outer_size.height() * inP_y_ratio);
}

QPoint Shape::getOutPoint(const QSize &outer_size) {
    return QPoint(outer_size.width() * outP_x_ratio, outer_size.height() * outP_y_ratio);
}

void Shape::paint(QPainter *painter, const QWidget *widget) {
    painter->save();
    QRect rec_l = widget->geometry();
    const qreal radius = 5;
    QPainterPath path;
    QRectF rect = QRect(rec_l.left() + 2, rec_l.top() + 2,
                        rec_l.width() - 4, rec_l.height() - 4);
    path.moveTo(rect.topRight() - QPointF(radius, 0));
    path.moveTo(rect.topRight() - QPointF(radius, 0));
    path.lineTo(rect.topLeft() + QPointF(radius, 0));
    path.quadTo(rect.topLeft(), rect.topLeft() + QPointF(0, radius));
    path.lineTo(rect.bottomLeft() + QPointF(0, -radius));
    path.quadTo(rect.bottomLeft(), rect.bottomLeft() + QPointF(radius, 0));
    path.lineTo(rect.bottomRight() - QPointF(radius, 0));
    path.quadTo(rect.bottomRight(), rect.bottomRight() + QPointF(0, -radius));
    path.lineTo(rect.topRight() + QPointF(0, radius));
    path.quadTo(rect.topRight(), rect.topRight() + QPointF(-radius, -0));
    painter->drawPath(path);
    painter->restore();
}

Shape::Shape(double x_ratio, double y_ratio, double w_ratio, double h_ratio, double inP_x_ratio, double inP_y_ratio,
             double outP_x_ratio, double outP_y_ratio)
        : x_ratio(x_ratio), y_ratio(y_ratio), w_ratio(w_ratio), h_ratio(h_ratio),
          inP_x_ratio(inP_x_ratio), inP_y_ratio(inP_y_ratio),
          outP_x_ratio(outP_x_ratio), outP_y_ratio(outP_y_ratio) {

}
