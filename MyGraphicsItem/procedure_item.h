#ifndef PROCEDURE_ITEM_H
#define PROCEDURE_ITEM_H

#include "myitem_base.h"

class Procedure_item : public Myitem_base
{

public:
    Procedure_item(QGraphicsItem *parent = 0);
    ~Procedure_item();

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE;

};

#endif // PROCEDURE_ITEM_H
