#ifndef PROCEDURE_ITEM_H
#define PROCEDURE_ITEM_H

#include "myitem_base.h"

class Procedure_item : public Myitem_base
{
public:

    enum LoopLimitType 
    {
        noType = -1, 
        Sequential, 
        if_else_join, 
        while_up,
        while_below, 
        doWhile_up, 
        doWhile_below
    };

    Procedure_item(QGraphicsItem *parent = 0);
    ~Procedure_item();

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE;

    void setNextItem(Myitem_base* nextItem, ArrowItem* arrow = nullptr) Q_DECL_OVERRIDE;
    Myitem_base* getNextItem(nextItemType whichType) Q_DECL_OVERRIDE;

    LoopLimitType getLoopLimitType() const;
    void setLoopLimitType(const LoopLimitType &value);


private:
    Myitem_base* nextItem = nullptr;

    LoopLimitType loopLimitType = noType; 
};

#endif 
