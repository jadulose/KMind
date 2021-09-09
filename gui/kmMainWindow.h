//
// Created by Hamlet on 2021/9/6.
//

#ifndef KMIND_KMMAINWINDOW_H
#define KMIND_KMMAINWINDOW_H

#include <QMainWindow>
#include "../core/kmNode.h"

QT_BEGIN_NAMESPACE
namespace Ui { class kmMainWindow; }
QT_END_NAMESPACE

class kmMainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit kmMainWindow(QWidget *parent = nullptr);

    ~kmMainWindow() override;

private slots:
    void displayMindMap();

    void displayOutline();

    void switchPanel();

//    void resizeEvent(QResizeEvent * event) override;

    void setScrollBarPos(int v, int h);

    void beginScrollBarMove();

    void moveScrollBarPos(double v, double h);

private:
    Ui::kmMainWindow *ui;
    kmNode *m_baseNode;
    kmNode *m_selectedNode;

    QPoint m_lastScrollBarPos;
};


#endif //KMIND_KMMAINWINDOW_H
