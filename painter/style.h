//
// Created by Hamlet on 2021/9/7.
//

#ifndef KMIND_STYLE_H
#define KMIND_STYLE_H

#include "styleUtil.h"

class Style {
public:
    static Style copy_style(Style *style);

    Style();

    explicit Style(Shape *shape);

    ~Style();

    void setShape(Shape *shape);

    [[nodiscard]] Shape *getShape() const { return m_shape; }

private:
    bool isNotDefault = false;
    State m_state;
    Shape *m_shape;
};


#endif //KMIND_STYLE_H
