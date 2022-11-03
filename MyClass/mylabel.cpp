#include <QMouseEvent>
#include "mylabel.h"

MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{

}

MyLabel::~MyLabel()
{

}

void MyLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
    {
        emit myLabClick(this->mylabtype);
    }

    QLabel::mouseReleaseEvent(ev);
}


