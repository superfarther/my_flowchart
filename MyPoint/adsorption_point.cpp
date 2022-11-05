#include "adsorption_point.h"
#include <QPen>
#include <QBrush>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsScene>
#include "MyGraphicsItem/myitem_base.h"

Adsorption_point::Adsorption_point(QGraphicsItem *parent, QObject *objParent) : MyPointBase(parent), QObject(objParent)
{
    this->setAcceptHoverEvents(true);

    QPen pen(Qt::black, 2);
    this->setPen(pen);

    this->setRadius(9);
}

Adsorption_point::Adsorption_point(QPointF pos, QGraphicsItem *parent, QObject *objParent) : MyPointBase(parent), QObject(objParent)
{
    QPen pen(Qt::black, 2);
    this->setPen(pen);

    this->setRadius(9);
    this->setPos(pos);
}

Adsorption_point::~Adsorption_point()
{

}

void Adsorption_point::my_hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QBrush brush(Qt::black, Qt::SolidPattern);
    this->setBrush(brush);
}

void Adsorption_point::my_hoverEnterEvent()
{
    QBrush brush(Qt::black, Qt::SolidPattern);
    this->setBrush(brush);
}

void Adsorption_point::my_hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    this->setBrush(Qt::NoBrush);
}

void Adsorption_point::my_hoverLeaveEvent()
{
    this->setBrush(Qt::NoBrush);
}

void Adsorption_point::my_mouseReleaseEvent()
{

}

void Adsorption_point::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit arrowPress(this);

        event->accept();    //防止press吸附点时，父图元的拖拽事件被触发
    }
    //MyPointBase::mousePressEvent(event);  若将事件传递给父对象，会导致父图元的拖拽事件被触发
}

void Adsorption_point::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit arrowMove(event->scenePos(), this);

    event->accept();  //似乎因为mousePress事件被accept，使得mouseMove事件不会被传递给父类，因此不写accept也无影响
    //MyPointBase::mouseMoveEvent(event);   暂不清楚mouseMove事件是否需要传递给父对象
}

void Adsorption_point::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit arrowRelease(event->scenePos());

        event->accept();
    }
    //MyPointBase::mouseReleaseEvent(event);    暂不清楚mouseRelease是否需要传递给父对象
}

Adsorption_point::connectArrowWhich Adsorption_point::getToArrowWhich() const
{
    return toArrowWhich;
}

void Adsorption_point::setToArrowWhich(const connectArrowWhich &value)
{
    toArrowWhich = value;
}

ArrowItem *Adsorption_point::getToArrow() const
{
    return toArrow;
}

void Adsorption_point::setToArrow(ArrowItem *value)
{
    toArrow = value;
}
