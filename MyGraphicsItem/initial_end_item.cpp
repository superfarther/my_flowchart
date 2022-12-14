#include "initial_end_item.h"
#include <QPen>
#include <QPainter>
#include <Qt>

Initial_end_item::Initial_end_item(QGraphicsItem *parent): Myitem_base(parent)
{
    setLenth(150);
    setWidth(80);
 
    QPen pen(Qt::black, 2);
    this->setPen(pen);

    initialize_adsPoint();
}

Initial_end_item::~Initial_end_item()
{

}

QRectF Initial_end_item::boundingRect() const
{
    qreal lenth = getLenth();
    qreal width = getWidth();
    return QRect(-lenth/2, -width/2, lenth, width);
}

void Initial_end_item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(this->pen());
    painter->setBrush(this->brush());
    painter->setRenderHint(QPainter::Antialiasing, true); 

    qreal lenth = getLenth();
    qreal width = getWidth();
    QRect rect = QRect(-lenth/2, -width/2, lenth, width); 
    painter->drawRoundedRect(rect, 35, 35);
 
}

void Initial_end_item::setNextItem(Myitem_base* nextItem, ArrowItem* arrow)
{
    Q_UNUSED(arrow);
    this->nextItem = nextItem;

    qDebug("ini图元指向 %s图元", typeid(*nextItem).name());
}

Myitem_base* Initial_end_item::getNextItem(Myitem_base::nextItemType whichType)
{
    if(whichType == noMatter){
 
        return this->nextItem;
    }
    else{
        qDebug("错误的参数传入：Initial_end_item::getNextItem(Myitem_base::nextItemType whichType)");
        exit(-1);
    }
}

