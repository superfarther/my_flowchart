#ifndef ARROW_ITEM_H
#define ARROW_ITEM_H

#include <QGraphicsLineItem>
class ArrowItem : public QGraphicsLineItem
{

public:
    ArrowItem(QGraphicsItem *parent=0);
    ~ArrowItem();

    QPointF getStartPoint() const;
    void setStartPoint(const QPointF &value);

    QPointF getEndPoint() const;
    void setEndPoint(const QPointF &value);

    //重写paint以设置反走样
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE;
private:
    QPointF startPoint;
    QPointF endPoint;
};

#endif // ARROW_ITEM_H
