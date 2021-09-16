#ifndef KNODEEDIT_H
#define KNODEEDIT_H

#include <QTextEdit>
#include <QKeyEvent>

class kmNodeEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit kmNodeEdit(QWidget *_parent = nullptr);

signals:
    void finish();

private slots:
    void focusOutEvent(QFocusEvent *e);
    void keyPressEvent(QKeyEvent *e);
};

#endif // KNODEEDIT_H
