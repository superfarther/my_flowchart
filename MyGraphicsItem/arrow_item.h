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
    //箭头的逻辑类型
    typedef enum arrowLogicType
    {
        noType = -1,    
        commonType,     
        trueType,       
        falseType       
    }arrowLogicType;

    //箭头的绘制类型
    typedef enum arrowPaintingType
    {
        straight = 0,      
        judge_rect_left = 1, 
        judge_right   
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
    QPainterPath shape() const Q_DECL_OVERRIDE; 

    void paintArrowCluster();         //绘制箭簇
    QPolygonF getArrowClusterShape(); //获得箭簇形状

    void arrowRepaintEvent(QPointF pos, Adsorption_point::connectArrowWhich toArrowWhich);  

    void identifyPaintingType();    
    arrowPaintingType getPaintingType() const;  

    void identifyBrokenLinePath();
    QPainterPath getBorkenLinePath() const; 

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;   
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;      

public slots:
    void mouseRightButtonSignalClick();  

private:
    QPointF startPoint;
    QPointF endPoint;

    QGraphicsPolygonItem* arrowCluster; //箭头的箭镞
    qreal arrowCluster_lenth;  

    Adsorption_point* tailToAdsPoint = nullptr;  //箭尾连接的吸附点
    Adsorption_point* clusterToAdsPoint = nullptr;   //箭簇连接的吸附点

    arrowLogicType logicType = noType;  //箭头的逻辑类型
    arrowPaintingType paintingType = straight;  //箭头的绘制类型
    QPainterPath brokenLinePath;    //折线绘制路径

    QGraphicsTextItem* text = nullptr;  //仅用于菱形框的分支提示

    QTimer *timer;
};

#endif // ARROW_ITEM_H
