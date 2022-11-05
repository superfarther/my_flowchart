#include <QPolygon>
#include "judge_item.h"

Judge_item::Judge_item(QGraphicsItem *parent) : Myitem_base(parent)
{
    setLenth(150);
    setWidth(80);
    //初始化画笔样式
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
    painter->setRenderHint(QPainter::Antialiasing, true); //反走样

    qreal lenth = getLenth();
    qreal width = getWidth();
    //QRect rect = QRect(-lenth/2, -width/2, lenth, width); //这个rect在scene坐标系中
    QPolygon polygon;
    polygon << QPoint(0, -width/2) << QPoint(lenth/2, 0)
            << QPoint(0, width/2) << QPoint(-lenth/2, 0);   //上右下左
    painter->drawPolygon(polygon);
    //painter->drawRoundedRect(rect, 35, 35);
    //painter->drawRect(rect);
}
