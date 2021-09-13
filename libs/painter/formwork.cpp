//
// Created by Hamlet on 2021/9/8.
//

#include "formwork.h"

Skeleton::Skeleton(Style *base_style, Style *main_style, Style *sub_style, Style *floatStyle)
        : m_baseStyle(base_style), m_mainStyle(main_style), m_subStyle(sub_style), m_floatStyle(floatStyle) {
}

Style *Skeleton::getStyle(kmNodeType type) {
    switch (type) {
        case kmNodeType::BaseTopic:
            return m_baseStyle;
        case kmNodeType::MainTopic:
            return m_mainStyle;
        case kmNodeType::FloatTopic:
            return m_floatStyle;
        default:
            return m_subStyle;
    }
}

Skeleton::~Skeleton() {
    delete m_baseStyle;
    delete m_mainStyle;
    delete m_subStyle;
    delete m_floatStyle;
}
