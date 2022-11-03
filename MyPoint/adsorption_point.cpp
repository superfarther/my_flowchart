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

    this->setRadius(7);
}

Adsorption_point::Adsorption_point(QPointF pos, QGraphicsItem *parent, QObject *objParent) : MyPointBase(parent), QObject(objParent)
{

    QPen pen(Qt::black, 2);
    this->setPen(pen);

    this->setRadius(7);
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

void Adsorption_point::my_hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    this->setBrush(Qt::NoBrush);
}

void Adsorption_point::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit arrowPress(this);

    event->accept();    //防止press吸附点时，父图元的拖拽事件被触发
}

void Adsorption_point::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit arrowMove(event->scenePos());
    /*
    QTransform transform;
    QGraphicsItem *item = this->scene()->itemAt(event->scenePos(), transform);
    if(item);
    {
        item->Myitem_base::my_hoverEnterEvent(event);
    }
    */

    MyPointBase::mouseMoveEvent(event);
    //event->accept();  似乎因为mousePress事件被accept，使得mouseMove事件不会被传递给父类，因此不需要accept mouseMove事件
}

void Adsorption_point::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit arrowRelease(event->scenePos());

    MyPointBase::mouseReleaseEvent(event);
}
