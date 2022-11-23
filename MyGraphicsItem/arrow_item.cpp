#include <QPen>
#include <QPainter>
#include <qmath.h>
#include <my_graphicsscene.h>
#include "arrow_item.h"

ArrowItem::ArrowItem(QGraphicsItem *parent, QObject *objParent) : QGraphicsLineItem(parent), QObject(objParent)
{
    this->setAcceptHoverEvents(true);
    QPen pen(Qt::black, 2);
    setPen(pen);

    this->arrowCluster_lenth = 16;

    this->text = new QGraphicsTextItem(this);
    timer = new QTimer(this);
    timer->setSingleShot(true); 
    connect(timer, &QTimer::timeout, this, &ArrowItem::mouseRightButtonSignalClick);
}

ArrowItem::~ArrowItem()
{

}

void ArrowItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing, true); 
    painter->setPen(QPen(Qt::black, 2));

    if(paintingType == straight){
        QGraphicsLineItem::paint(painter, option, widget);
    }
    else if(paintingType == judge_rect_left){
        identifyBrokenLinePath();
        painter->drawPath(brokenLinePath);
    }
    else if(paintingType == judge_right){
        identifyBrokenLinePath();
        painter->drawPath(brokenLinePath);
    }
}

QPainterPath ArrowItem::shape() const
{
    if(paintingType == straight){
        return QGraphicsLineItem::shape();
    }
    else if(paintingType == judge_rect_left){
        return brokenLinePath;
    }
    else if(paintingType == judge_right){
        return brokenLinePath;
    }
}

void ArrowItem::paintArrowCluster()
{
    arrowCluster = new ArrowCluster(getArrowClusterShape(), this);
}

QPolygonF ArrowItem::getArrowClusterShape()
{
    if(paintingType == straight){
        QLineF line(startPoint, endPoint);
        qreal angleZ = line.angle(); 
        qreal radianZ = angleZ*PAI/180; 
        qreal radianAlpha = 11*PAI/6 - radianZ; 
        QPointF pointC(endPoint.x() - arrowCluster_lenth*cos(radianAlpha),
                       endPoint.y() - arrowCluster_lenth*sin(radianAlpha));
        QPointF pointD(endPoint.x() - arrowCluster_lenth*sin(PAI/6-radianAlpha),
                       endPoint.y() - arrowCluster_lenth*cos(PAI/6-radianAlpha));
        QPolygonF arrowClusterShape;
        arrowClusterShape << pointC << pointD << endPoint;
        return arrowClusterShape;
    }
    else if(paintingType == judge_rect_left){
        QPointF pointA(endPoint.x() - sqrt(3)*arrowCluster_lenth/2,
                       endPoint.y() - arrowCluster_lenth/2);
        QPointF pointB(endPoint.x() - sqrt(3)*arrowCluster_lenth/2,
                       endPoint.y() + arrowCluster_lenth/2);
        QPolygonF arrowClusterShape;
        arrowClusterShape << pointA << pointB << endPoint;
        return arrowClusterShape;
    }
    else if(paintingType == judge_right){
        QPointF pointA(endPoint.x() - arrowCluster_lenth/2,
                       endPoint.y() - sqrt(3)*arrowCluster_lenth/2);
        QPointF pointB(endPoint.x() + arrowCluster_lenth/2,
                       endPoint.y() - sqrt(3)*arrowCluster_lenth/2);
        QPolygonF arrowClusterShape;
        arrowClusterShape << pointA << pointB << endPoint;
        return arrowClusterShape;
    }
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
    arrowCluster->setPolygon(getArrowClusterShape()); 
 
    if(paintingType == straight){
        text->setPos((this->startPoint+this->endPoint)/2);
    }
    else{
        text->setPos(brokenLinePath.pointAtPercent(0.5));
    }
 
}

void ArrowItem::identifyPaintingType()
{
    if(clusterToAdsPoint != nullptr){
        Myitem_base* startItem = dynamic_cast<Myitem_base*>(tailToAdsPoint->parentItem()); 
        Myitem_base* endItem =  dynamic_cast<Myitem_base*>(clusterToAdsPoint->parentItem()); 
        if(tailToAdsPoint == startItem->getLeft_adsPoint() && clusterToAdsPoint == endItem->getLeft_adsPoint()
           && typeid(*startItem) != typeid(Initial_end_item) && typeid(*endItem) != typeid(Initial_end_item))
        {
            paintingType = judge_rect_left;
            qDebug("该箭头是judge_rect_left");
        }
        else if(startItem->getBelow_adsPoint()->getToArrow() != nullptr && typeid(*startItem) == typeid(Judge_item)
                && tailToAdsPoint == startItem->getRight_adsPoint())
        {
            paintingType = judge_right;
            qDebug("该箭头是judge_right");
        }
    }
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
        Myitem_base* startItem = dynamic_cast<Myitem_base*>(this->getTailToAdsPoint()->parentItem());
        if(typeid(*startItem) == typeid(Judge_item) && this->getClusterToAdsPoint() != nullptr)
        {
            timer->stop();

            this->setLogicType(falseType);
            Myitem_base* endItem = dynamic_cast<Myitem_base*>(this->getClusterToAdsPoint()->parentItem());
            startItem->setNextItem(endItem, this);

 
            text->setPlainText("F");
            text->adjustSize();
            if(paintingType == straight){
                text->setPos((this->startPoint+this->endPoint)/2);
            }
            else{
                text->setPos(brokenLinePath.pointAtPercent(0.5));
            }

            QFont font;
            font.setBold(true);
            font.setFamily("微软雅黑");
            font.setPointSize(13);
            text->setFont(font);
 
        }
    }

 
}

void ArrowItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        Myitem_base* startItem = dynamic_cast<Myitem_base*>(this->getTailToAdsPoint()->parentItem());
        if(typeid(*startItem) == typeid(Judge_item) && this->getClusterToAdsPoint() != nullptr)
        {
            timer->start(300);
        }
    }

    QGraphicsLineItem::mousePressEvent(event);
}

void ArrowItem::mouseRightButtonSignalClick()
{
    this->setLogicType(trueType);
    Myitem_base* startItem = dynamic_cast<Myitem_base*>(this->getTailToAdsPoint()->parentItem());
    Myitem_base* endItem = dynamic_cast<Myitem_base*>(this->getClusterToAdsPoint()->parentItem());
    startItem->setNextItem(endItem, this);

 
    text->setPlainText("T");
    text->adjustSize();
    if(paintingType == straight){
        text->setPos((this->startPoint+this->endPoint)/2);
    }
    else{
        text->setPos(brokenLinePath.pointAtPercent(0.5));
    }

    QFont font;
    font.setBold(true);
    font.setFamily("微软雅黑");
    font.setPointSize(13);
    text->setFont(font);
 
}

QPainterPath ArrowItem::getBorkenLinePath() const
{
    return brokenLinePath;
}

ArrowItem::arrowPaintingType ArrowItem::getPaintingType() const
{
    return paintingType;
}

void ArrowItem::identifyBrokenLinePath()
{
    if(paintingType != straight){
        qreal x1 = startPoint.x();
        qreal y1 = startPoint.y();
        qreal x2 = endPoint.x();
        qreal y2 = endPoint.y();

        QPainterPath path;
        if(paintingType == judge_rect_left){
            QPointF p1(x1 - 66, y1);
            QPointF p2(x1 - 66, y2);
            path.moveTo(startPoint);
            path.lineTo(p1);
            path.lineTo(p2);
            path.lineTo(endPoint);
            brokenLinePath = path;
            return;
        }
        else if(paintingType == judge_right){
            QPointF p1(x1+66, y1);
            QPointF p2(x1+66, y2-66);
            QPointF p3(x2, y2-66);
            path.moveTo(startPoint);
            path.lineTo(p1);
            path.lineTo(p2);
            path.lineTo(p3);
            path.lineTo(endPoint);
            brokenLinePath = path;
            return;
        }
    }
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
