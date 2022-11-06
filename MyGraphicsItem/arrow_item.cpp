#include <QPen>
#include <QPainter>
#include <qmath.h>
#include <my_graphicsscene.h>
#include "arrow_item.h"

ArrowItem::ArrowItem(QGraphicsItem *parent) : QGraphicsLineItem(parent)
{
    this->setAcceptHoverEvents(true);

    QPen pen(Qt::black, 2);
    setPen(pen);

    this->arrowCluster_lenth = 16;
    this->text = new QGraphicsTextItem(this);
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
    this->text->setPos((this->startPoint+this->endPoint)/2);    //text跟随箭头移动
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

void ArrowItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QPen pen(Qt::green, 2);
    this->setPen(pen);
    this->setCursor(Qt::PointingHandCursor);

    QGraphicsLineItem::hoverEnterEvent(event);
}

void ArrowItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QPen pen(Qt::black, 2);
    setPen(pen);
    this->setCursor(Qt::ArrowCursor);

    QGraphicsLineItem::hoverLeaveEvent(event);
}

void ArrowItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        text->setPlainText("T");
        //text->setHtml(QString("<div style='background-color: #DCDCDC;'>") + "T" + "</div>");
        text->setPos((this->startPoint+this->endPoint)/2);
        text->adjustSize();

        QFont font;
        font.setBold(true);
        font.setFamily("微软雅黑");
        font.setPointSize(13);
        text->setFont(font);
        //this->scene()->addItem(text); 因为text是箭头的子对象，因此不需手动添加到scene中
    }
    QGraphicsLineItem::mouseDoubleClickEvent(event);
}

QGraphicsTextItem *ArrowItem::getText() const
{
    return text;
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
