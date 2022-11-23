#ifndef ADSORPTION_POINT_H
#define ADSORPTION_POINT_H

#include "mypointbase.h"

class ArrowItem;

class Adsorption_point : public QObject, public MyPointBase
{
    Q_OBJECT

public:
 
    typedef enum connectArrowWhich
    {
        noArrow = -1,
        arrowTail,
        arrowCluster
    }connectArrowWhich;

    Adsorption_point(QGraphicsItem *parent=0, QObject *objParent = 0);
    Adsorption_point(QPointF pos, QGraphicsItem *parent=0, QObject *objParent = 0);
    ~Adsorption_point();

    ArrowItem *getToArrow() const;
    void setToArrow(ArrowItem *value);

    connectArrowWhich getToArrowWhich() const;
    void setToArrowWhich(const connectArrowWhich &value);

     
     
    void my_hoverEnterEvent(QGraphicsSceneHoverEvent *event); 
    void my_hoverEnterEvent(); 

    void my_hoverLeaveEvent(QGraphicsSceneHoverEvent *event); 
    void my_hoverLeaveEvent(); 

    void my_mouseReleaseEvent(); 

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

signals:
    void arrowPress(Adsorption_point *startAdsPoint); 
    void arrowMove(QPointF arrow_movingPoint, Adsorption_point *startAdsPoint); 
    void arrowRelease(QPointF arrow_releasePoint); 

private:
    ArrowItem* toArrow = nullptr; 
    connectArrowWhich toArrowWhich = noArrow; 
};

#endif 
