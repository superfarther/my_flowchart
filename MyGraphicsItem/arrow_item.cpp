#include <QPen>
#include <QPainter>
#include "arrow_item.h"

ArrowItem::ArrowItem(QGraphicsItem *parent) : QGraphicsLineItem(parent)
{
    QPen pen(Qt::black, 2);
    setPen(pen);
}

ArrowItem::~ArrowItem()
{

}

void ArrowItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing, true);   //反走样
    QGraphicsLineItem::paint(painter, option, widget);
}

QPointF ArrowItem::getStartPoint() const
{
    return startPoint;
}

void ArrowItem::setStartPoint(const QPointF &value)
{
    startPoint = value;
}

QPointF ArrowItem::getEndPoint() const
{
    return endPoint;
}

void ArrowItem::setEndPoint(const QPointF &value)
{
    endPoint = value;
}
