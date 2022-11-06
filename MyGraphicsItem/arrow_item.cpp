#include <QPen>
#include <QPainter>
#include <qmath.h>
#include <my_graphicsscene.h>
#include "arrow_item.h"

ArrowItem::ArrowItem(QGraphicsItem *parent) : QGraphicsLineItem(parent)
{
    QPen pen(Qt::black, 2);
    setPen(pen);

    this->arrowCluster_lenth = 16;
}

ArrowItem::~ArrowItem()
{

}

void ArrowItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing, true);   //反走样
    QGraphicsLineItem::paint(painter, option, widget);
}

void ArrowItem::paintArrowCluster()
{
    //绘制箭簇
    QLineF line(startPoint, endPoint);
    qreal angleZ = line.angle(); //箭头倾斜角度
    qreal radianZ = angleZ*PAI/180; //箭头倾斜弧度
    qreal radianAlpha = 11*PAI/6 - radianZ;  //角α
    /*
    QPointF pointC(endPoint.x() - arrowCluster_lenth/2*cos(radianAlpha),
                   endPoint.y() + arrowCluster_lenth/2*sin(radianAlpha));
    QPointF pointD(endPoint.x() + arrowCluster_lenth/2*cos(radianAlpha),
                   endPoint.y() - arrowCluster_lenth/2*sin(radianAlpha));
    QPointF pointE(endPoint.x() + sqrt(3)*arrowCluster_lenth/2*cos(2*PAI-radianZ),
                   endPoint.y() + sqrt(3)*arrowCluster_lenth/2*sin(2*PAI-radianZ));
    */
    QPointF pointC(endPoint.x() - arrowCluster_lenth*cos(radianAlpha),
                   endPoint.y() - arrowCluster_lenth*sin(radianAlpha));
    QPointF pointD(endPoint.x() - arrowCluster_lenth*sin(PAI/6-radianAlpha),
                   endPoint.y() - arrowCluster_lenth*cos(PAI/6-radianAlpha));
    QPolygonF arrowClusterShape;
    arrowClusterShape << pointC << pointD << endPoint;
    arrowCluster = new ArrowCluster(arrowClusterShape, this);
}

void ArrowItem::arrowRepaintEvent(QPointF pos, Adsorption_point::connectArrowWhich toArrowWhich)
{
    if(toArrowWhich == Adsorption_point::arrowTail)
    {
        startPoint = pos;
    }
    else
    {
        endPoint = pos;
    }
    QLineF line(startPoint, endPoint);
    this->setLine(line);
    this->arrowClusterRepaintEvent();
    //update(this->boundingRect()); 暂不清楚是否需要update
}

void ArrowItem::arrowClusterRepaintEvent()
{
    //绘制箭簇
    QLineF line(startPoint, endPoint);
    qreal angleZ = line.angle(); //箭头倾斜角度
    qreal radianZ = angleZ*PAI/180; //箭头倾斜弧度
    qreal radianAlpha = 11*PAI/6 - radianZ;  //角α
    QPointF pointC(endPoint.x() - arrowCluster_lenth*cos(radianAlpha),
                   endPoint.y() - arrowCluster_lenth*sin(radianAlpha));
    QPointF pointD(endPoint.x() - arrowCluster_lenth*sin(PAI/6-radianAlpha),
                   endPoint.y() - arrowCluster_lenth*cos(PAI/6-radianAlpha));
    QPolygonF arrowClusterShape;
    arrowClusterShape << pointC << pointD << endPoint;
    arrowCluster->setPolygon(arrowClusterShape);
}

ArrowItem::arrowLogicType ArrowItem::getLogicType() const
{
    return logicType;
}

void ArrowItem::setLogicType(const arrowLogicType &value)
{
    logicType = value;
}

Adsorption_point *ArrowItem::getTailToAdsPoint() const
{
    return tailToAdsPoint;
}

void ArrowItem::setTailToAdsPoint(Adsorption_point *value)
{
    tailToAdsPoint = value;
}

Adsorption_point *ArrowItem::getClusterToAdsPoint() const
{
    return clusterToAdsPoint;
}

void ArrowItem::setClusterToAdsPoint(Adsorption_point *value)
{
    clusterToAdsPoint = value;
}

qreal ArrowItem::getArrowCluster_lenth() const
{
    return arrowCluster_lenth;
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
