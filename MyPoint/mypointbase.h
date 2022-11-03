#ifndef MYPOINTBASE_H
#define MYPOINTBASE_H

#include <QPointF>
#include <QGraphicsEllipseItem>
#include <QPainter>

class MyPointBase : public QGraphicsEllipseItem
{

public:
    MyPointBase(QGraphicsItem *parent = 0);
    ~MyPointBase();

    QPointF getPos() const;
    void setPos(const QPointF &value);

    qreal getRadius() const;
    void setRadius(const qreal &value);

private:
    QPointF pos;   //点的中心坐标（也即圆心坐标），相对于scnen坐标系
    qreal radius;
};

#endif // MYPOINTBASE_H
