//
// Created by Hamlet on 2021/9/7.
//

#include "style.h"

Style Style::copy_style(Style *style) {
    Style n_style;
    n_style.m_state = style->m_state;
    n_style.m_shape = style->m_shape;
    return std::move(n_style);
}

Style::Style() : m_state(State::Default), m_shape(nullptr) {
}

void Style::setShape(Shape *shape) {
    if (shape == nullptr)
        return;
    if (m_shape == nullptr) {
        m_shape = shape;
        return;
    }
    if (isNotDefault)
        delete m_shape;
    m_shape = shape;
    isNotDefault = true;
}

Style::~Style() {
    if (isNotDefault)
        delete m_shape;
}
