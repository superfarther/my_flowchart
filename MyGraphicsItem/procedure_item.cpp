#include "procedure_item.h"

Procedure_item::Procedure_item(QGraphicsItem *parent) : Myitem_base(parent)
{
    setLenth(150);
    setWidth(80);

    QPen pen(Qt::black, 2);
    this->setPen(pen);

    initialize_adsPoint();
}

Procedure_item::~Procedure_item()
{

}

QRectF Procedure_item::boundingRect() const
{
    qreal lenth = getLenth();
    qreal width = getWidth();
    return QRect(-lenth/2, -width/2, lenth, width);
}

void Procedure_item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(this->pen());
    painter->setBrush(this->brush());
    painter->setRenderHint(QPainter::Antialiasing, true); //反走样

    qreal lenth = getLenth();
    qreal width = getWidth();
    QRect rect = QRect(-lenth/2, -width/2, lenth, width); 
    painter->drawRect(rect);
}

void Procedure_item::setNextItem(Myitem_base* nextItem, ArrowItem* arrow)
{
    Q_UNUSED(arrow);
    this->nextItem = nextItem;

    qDebug("pro图元指向 %s图元", typeid(*nextItem).name());
}
