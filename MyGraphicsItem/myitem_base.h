#ifndef MYITEM_BASE_H
#define MYITEM_BASE_H

#include <QAbstractGraphicsShapeItem>
#include <QPen>
#include <QPainter>
#include <QGraphicsScene>
#include <QTextBlockFormat>
#include <QTextCursor>
#include "MyPoint/adsorption_point.h"
#include "arrow_item.h"

class Myitem_base : public QAbstractGraphicsShapeItem
{

public:
    Myitem_base(QGraphicsItem *parent = 0);
    ~Myitem_base();

    qreal getLenth() const;
    void setLenth(const qreal &value);

    qreal getWidth() const;
    void setWidth(const qreal &value);

    QPointF getCentral_point();

    Adsorption_point *getTop_adsPoint() const;
    Adsorption_point *getBelow_adsPoint() const;
    Adsorption_point *getLeft_adsPoint() const;
    Adsorption_point *getRight_adsPoint() const;
    void initialize_adsPoint(); 
    void update_adsPoint(); 
    void show_adsPoint();  
    void disappear_adsPoint();  
    Adsorption_point* whichAdsPoint(QPointF eventPos);  //通过hover事件的坐标，判断发生的hover事件是否与吸附点有关。如果有关，返回其指针

    void my_hoverEnterEvent();  
    void my_hoverLeaveEvent();

    virtual void setNextItem(Myitem_base* nextItem, ArrowItem* arrow = nullptr) = 0;    //纯虚函数

    void initialize_text();

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

private:
    qreal lenth;        //对应boundingrect中的rect的长
    qreal width;        // qreal = double

    QPointF central_point;   //图元中心点坐标

    Adsorption_point *top_adsPoint;
    Adsorption_point *below_adsPoint;
    Adsorption_point *left_adsPoint;     //左吸附点
    Adsorption_point *right_adsPoint;    //右吸附点

    QGraphicsTextItem* text;
};

#endif // MYITEM_BASE_H
