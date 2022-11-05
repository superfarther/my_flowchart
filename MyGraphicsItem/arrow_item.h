#ifndef ARROW_ITEM_H
#define ARROW_ITEM_H

#include <QGraphicsLineItem>
#include "arrowcluster.h"
#include "MyPoint/adsorption_point.h"
#define PAI 3.14159265358979



class ArrowItem : public QGraphicsLineItem
{

public:
    ArrowItem(QGraphicsItem *parent=0);
    ~ArrowItem();

    QPointF getStartPoint() const;
    void setStartPoint(const QPointF &value);

    QPointF getEndPoint() const;
    void setEndPoint(const QPointF &value);

    qreal getArrowCluster_lenth() const;

    Adsorption_point *getTailToAdsPoint() const;
    void setTailToAdsPoint(Adsorption_point *value);

    Adsorption_point *getClusterToAdsPoint() const;
    void setClusterToAdsPoint(Adsorption_point *value);

    //重写paint以设置反走样
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE;

    void paintArrowCluster();

    //item被拖拽时，重绘相应的箭头
    //item若连接箭尾，则参数pos赋给相应箭头的startPoint
    //item若连接箭簇，则参数pos赋给相应箭头的endPoint
    void arrowRepaintEvent(QPointF pos, Adsorption_point::connectArrowWhich toArrowWhich);
    void arrowClusterRepaintEvent();

private:
    QPointF startPoint; //相对于scene坐标系
    QPointF endPoint;

    QGraphicsPolygonItem* arrowCluster; //箭头的箭镞
    qreal arrowCluster_lenth;   //箭簇三角形的边长

    Adsorption_point* tailToAdsPoint = nullptr;  //箭尾连接的吸附点
    Adsorption_point* clusterToAdsPoint = nullptr;   //箭簇连接的吸附点
};

#endif // ARROW_ITEM_H
