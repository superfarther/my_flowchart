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
    timer->setSingleShot(true); //设置单次计时器
    connect(timer, &QTimer::timeout, this, &ArrowItem::mouseRightButtonSignalClick);
}

ArrowItem::~ArrowItem()
{

}

void ArrowItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing, true);   //反走样
    if(paintingType == straight){
        QGraphicsLineItem::paint(painter, option, widget);
    }
}

void ArrowItem::paintArrowCluster()
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

void ArrowItem::identifyPaintingType()
{
    if(clusterToAdsPoint != nullptr){
        Myitem_base* startItem = dynamic_cast<Myitem_base*>(tailToAdsPoint->parentItem());  //该箭头连接的起始图元
        Myitem_base* endItem =  dynamic_cast<Myitem_base*>(clusterToAdsPoint->parentItem());  //该箭头连接的终止图元
        if(tailToAdsPoint == startItem->getLeft_adsPoint() && clusterToAdsPoint == endItem->getLeft_adsPoint()
           && typeid(*startItem) != typeid(Initial_end_item) && typeid(*endItem) != typeid(Initial_end_item))
        {
            paintingType = judge_rect_left;
            qDebug("该箭头是judge_rect_left");
        }
        else if(startItem->getBelow_adsPoint() != nullptr && typeid(*startItem) == typeid(Judge_item)
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
            //text->setHtml(QString("<div style='background-color: #DCDCDC;'>") + "T" + "</div>");
            text->setPos((this->startPoint+this->endPoint)/2);
            text->adjustSize();

            QFont font;
            font.setBold(true);
            font.setFamily("微软雅黑");
            font.setPointSize(13);
            text->setFont(font);
            //this->scene()->addItem(text); 因为text是箭头的子对象，所以不需手动添加到scene中
        }
    }

    //QGraphicsLineItem::mouseDoubleClickEvent(event);  若将双击事件传递给父类，会导致计时器被重新启动，why???
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
    //text->setHtml(QString("<div style='background-color: #DCDCDC;'>") + "T" + "</div>");
    text->setPos((this->startPoint+this->endPoint)/2);
    text->adjustSize();

    QFont font;
    font.setBold(true);
    font.setFamily("微软雅黑");
    font.setPointSize(13);
    text->setFont(font);
    //this->scene()->addItem(text); 因为text是箭头的子对象，所以不需手动添加到scene中
}

ArrowItem::arrowPaintingType ArrowItem::getPaintingType() const
{
    return paintingType;
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
