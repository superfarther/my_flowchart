#include <QPolygon>
#include "judge_item.h"

Judge_item::Judge_item(QGraphicsItem *parent) : Myitem_base(parent)
{
    setLenth(150);
    setWidth(80);
 
    QPen pen(Qt::black, 2);
    this->setPen(pen);

    initialize_adsPoint();
}

Judge_item::~Judge_item()
{

}

QRectF Judge_item::boundingRect() const
{
    qreal lenth = getLenth();
    qreal width = getWidth();
    return QRect(-lenth/2, -width/2, lenth, width);
}

void Judge_item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(this->pen());
    painter->setBrush(this->brush());
    painter->setRenderHint(QPainter::Antialiasing, true); 

    qreal lenth = getLenth();
    qreal width = getWidth();
 
    QPolygon polygon;
    polygon << QPoint(0, -width/2) << QPoint(lenth/2, 0)
            << QPoint(0, width/2) << QPoint(-lenth/2, 0); 
    painter->drawPolygon(polygon);
 
 
}

void Judge_item::setNextItem(Myitem_base* nextItem, ArrowItem* arrow)
{
    if(arrow->getLogicType() == ArrowItem::falseType)
    {
        this->nextFalseItem = nextItem;

        qDebug("judge图元的F分支指向 %s图元", typeid(*nextItem).name());
    }
    else
    {
        this->nextTrueItem = nextItem;

        qDebug("judge图元的T分支指向 %s图元", typeid(*nextItem).name());
    }
}

Myitem_base *Judge_item::getNextItem(Myitem_base::nextItemType whichType)
{
    if(whichType == nextTrueType){
 
        return this->nextTrueItem;
    }
    else if(whichType == nextFalseType){
 
        return this->nextFalseItem;
    }
    else{
        qDebug("错误的参数传入：Judge_item::getNextItem(Myitem_base::nextItemType whichType)");
        exit(-1);
    }
}

Judge_item::LoopLimitType Judge_item::getLoopLimitType() const
{
    return loopLimitType;
}

void Judge_item::setLoopLimitType(const LoopLimitType &value)
{
    loopLimitType = value;
}

