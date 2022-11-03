#include "mypointbase.h"

MyPointBase::MyPointBase(QGraphicsItem *parent): QGraphicsEllipseItem(parent)
{

}

MyPointBase::~MyPointBase()
{

}

QPointF MyPointBase::getPos() const
{
    return pos;
}

void MyPointBase::setPos(const QPointF &value)
{
    pos = value;
}

qreal MyPointBase::getRadius() const
{
    return radius;
}

void MyPointBase::setRadius(const qreal &value)
{
    radius = value;
}

