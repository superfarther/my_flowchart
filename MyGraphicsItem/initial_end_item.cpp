#include "initial_end_item.h"
#include <QPen>
#include <QPainter>
#include <Qt>

Initial_end_item::Initial_end_item(QGraphicsItem *parent): Myitem_base(parent)
{
    setLenth(150);
    setWidth(80);
    //初始化画笔样式
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
    painter->setRenderHint(QPainter::Antialiasing, true); //反走样

    qreal lenth = getLenth();
    qreal width = getWidth();
    QRect rect = QRect(-lenth/2, -width/2, lenth, width); //这个rect在scene坐标系中
    painter->drawRoundedRect(rect, 35, 35);
    //painter->drawRect(rect);
}
