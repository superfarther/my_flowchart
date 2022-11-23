#ifndef JUDGE_ITEM_H
#define JUDGE_ITEM_H

#include "myitem_base.h"

class Judge_item : public Myitem_base
{
public:

    typedef enum LoopLimitType 
    {
        noType = -1, 
        noloop, 
        while_up, 
        while_below,
        doWhile_up,
        doWhile_below 
    }LoopLimitType;

    Judge_item(QGraphicsItem *parent = 0);
    ~Judge_item();

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE;

    void setNextItem(Myitem_base* nextItem, ArrowItem* arrow = nullptr) Q_DECL_OVERRIDE; 
    Myitem_base* getNextItem(nextItemType whichType) Q_DECL_OVERRIDE;
    
    LoopLimitType getLoopLimitType() const;
    void setLoopLimitType(const LoopLimitType &value);


private:
    Myitem_base* nextTrueItem = nullptr;
    Myitem_base* nextFalseItem = nullptr;

    LoopLimitType loopLimitType = noType; 
};

#endif 
