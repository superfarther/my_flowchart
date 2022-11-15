#ifndef ARROW_ITEM_H
#define ARROW_ITEM_H

#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QFont>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include "arrowcluster.h"
#include "MyPoint/adsorption_point.h"
#define PAI 3.14159265358979

class ArrowItem : public QObject, public QGraphicsLineItem
{
    Q_OBJECT

public:
    //箭头的逻辑类型，由引出箭头的图元决定
    typedef enum arrowLogicType
    {
        noType = -1,    //暂不确定
        commonType,     //普通箭头
        trueType,       //菱形框的T分支
        falseType       //菱形框的F分支
    }arrowLogicType;

    //箭头的绘制类型
    typedef enum arrowPaintingType
    {
        straight = 0,       //直线
        judge_rect_left = 1,    //菱形左吸附点和矩形左吸附点相连，WHILE/DO-WHILE
        judge_right    //菱形右吸附点引出的箭头，且该菱形下吸附点已经引出了箭头，WHILE
    }arrowPaintingType;

    ArrowItem(QGraphicsItem *parent=0, QObject *objParent=0);
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

    arrowLogicType getLogicType() const;
    void setLogicType(const arrowLogicType &value);

    QGraphicsTextItem *getText() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE;

    void paintArrowCluster();

    //item被拖拽时，重绘相应的箭头
    //item若连接箭尾，则参数pos赋给相应箭头的startPoint
    //item若连接箭簇，则参数pos赋给相应箭头的endPoint
    void arrowRepaintEvent(QPointF pos, Adsorption_point::connectArrowWhich toArrowWhich);
    void arrowClusterRepaintEvent();

    void identifyPaintingType();    //标识（设置）箭头的绘制类型
    arrowPaintingType getPaintingType() const;  //获得箭头的绘制类型

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;    //右键双击，设置菱形框的F分支
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;        //右键单击，设置菱形框的T分支

public slots:
    void mouseRightButtonSignalClick();  //创建一个箭头的单击函数，以区分右键单击和双击

private:
    QPointF startPoint; //相对于scene坐标系
    QPointF endPoint;

    QGraphicsPolygonItem* arrowCluster; //箭头的箭镞
    qreal arrowCluster_lenth;   //箭簇三角形的边长

    Adsorption_point* tailToAdsPoint = nullptr;  //箭尾连接的吸附点
    Adsorption_point* clusterToAdsPoint = nullptr;   //箭簇连接的吸附点

    arrowLogicType logicType = noType;  //箭头的逻辑类型,初始时不确定
    arrowPaintingType paintingType = straight;  //箭头的绘制类型，初始为直线

    QGraphicsTextItem* text = nullptr;  //仅用于菱形框的分支提示

    QTimer *timer;
};

#endif // ARROW_ITEM_H
