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

    ~Style();

    void setShape(Shape *shape);

private:
    bool isNotDefault = false;
    State m_state;
    Shape *m_shape;
};


#endif //KMIND_STYLE_H
