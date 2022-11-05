#ifndef INITIAL_END_ITEM_H
#define INITIAL_END_ITEM_H

#include "myitem_base.h"

class Initial_end_item : public Myitem_base
{

public:
    Initial_end_item(QGraphicsItem *parent = 0);
    ~Initial_end_item();

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE;

private:
    Myitem_base* nextItem = nullptr;
};

#endif // INITIAL_END_ITEM_H
