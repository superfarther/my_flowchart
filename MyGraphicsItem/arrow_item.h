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
 
    typedef enum arrowLogicType
    {
        noType = -1, 
        commonType, 
        trueType, 
        falseType 
    }arrowLogicType;

 
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

    void paintArrowCluster(); 
    QPolygonF getArrowClusterShape(); 

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

    QGraphicsPolygonItem* arrowCluster; 
    qreal arrowCluster_lenth; 

    Adsorption_point* tailToAdsPoint = nullptr; 
    Adsorption_point* clusterToAdsPoint = nullptr; 

    arrowLogicType logicType = noType; 
    arrowPaintingType paintingType = straight; 
    QPainterPath brokenLinePath; 

    QGraphicsTextItem* text = nullptr; 

    QTimer *timer;
};

#endif 
