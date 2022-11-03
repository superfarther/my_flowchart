#ifndef MYITEM_BASE_H
#define MYITEM_BASE_H

#include <QAbstractGraphicsShapeItem>
#include <QPen>
#include <QPainter>
#include <QGraphicsScene>
#include "MyPoint/adsorption_point.h"

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
    //Central_point在mouseMoveEvent中自动更新

    Adsorption_point *getTop_adsPoint() const;
    Adsorption_point *getBelow_adsPoint() const;
    Adsorption_point *getLeft_adsPoint() const;
    Adsorption_point *getRight_adsPoint() const;
    void initialize_adsPoint(); //初始化吸附点
    void update_adsPoint(); //更新吸附点
    void show_adsPoint();   //设置吸附点可见
    void disappear_adsPoint();  //设置吸附点不可见
    Adsorption_point* whichAdsPoint(QPointF eventPos);  //通过hover事件的坐标，判断发生的hover事件是否与吸附点有关。如果有关，返回其指针

    void my_hoverEnterEvent(QGraphicsSceneMouseEvent *event);   //吸附点触发mouseMove事件时，光标移入图元

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

private:
    qreal lenth;        //对应boundingrect中的rect的长
    qreal width;        // qreal = double

    QPointF central_point;   //图元中心点坐标，相对于scene坐标系

    Adsorption_point *top_adsPoint;
    Adsorption_point *below_adsPoint;
    Adsorption_point *left_adsPoint;     //左吸附点
    Adsorption_point *right_adsPoint;    //右吸附点
};

#endif // MYITEM_BASE_H
