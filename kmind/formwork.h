//
// Created by Hamlet on 2021/9/8.
//

#ifndef KMIND_FORMWORK_H
#define KMIND_FORMWORK_H

#include <QList>
#include "style.h"
#include "kmNodeType.h"

class Style;

class Skeleton {
public:
    static QList<Skeleton *> ALL_SKELETON;

    Skeleton(Style *base_style, Style *main_style, Style *sub_style, Style *floatStyle);

    ~Skeleton();

    Style *getStyle(kmNodeType type);

private:
    Style *m_baseStyle;
    Style *m_mainStyle;
    Style *m_subStyle;
    Style *m_floatStyle;
};

class ColorTheme {

};


#endif //KMIND_FORMWORK_H
