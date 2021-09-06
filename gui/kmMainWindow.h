//
// Created by Hamlet on 2021/9/6.
//

#ifndef KMIND_KMMAINWINDOW_H
#define KMIND_KMMAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::kmMainWindow *ui;
};


#endif //KMIND_KMMAINWINDOW_H
