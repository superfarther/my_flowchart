#ifndef JUDGE_ITEM_H
#define JUDGE_ITEM_H

#include "myitem_base.h"

class Judge_item : public Myitem_base
{

public:
    Judge_item(QGraphicsItem *parent = 0);
    ~Judge_item();

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE;

    void setNextItem(Myitem_base* nextItem, ArrowItem* arrow = nullptr) Q_DECL_OVERRIDE;    //对菱形框来说，T分支和F分支由传入的arrow决定

private:
    Myitem_base* nextTrueItem = nullptr;
    Myitem_base* nextFalseItem = nullptr;
};

#endif // JUDGE_ITEM_H
