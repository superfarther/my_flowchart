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
    QPointF pos; 
    qreal radius;
};

#endif 
