#include "kmnodeedit.h"

kmNodeEdit::kmNodeEdit(QWidget *p)
{
    this->setParent(p);
}

void kmNodeEdit::focusOutEvent(QFocusEvent *e)
{
    emit finish();
}

void kmNodeEdit::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Return)
    {
        emit finish();
    }
}
