#ifndef ADSORPTION_POINT_H
#define ADSORPTION_POINT_H

#include "mypointbase.h"

class Adsorption_point : public QObject, public MyPointBase
{
    Q_OBJECT

public:
    Adsorption_point(QGraphicsItem *parent=0, QObject *objParent = 0);
    Adsorption_point(QPointF pos, QGraphicsItem *parent=0, QObject *objParent = 0);
    ~Adsorption_point();

/***在图元重叠的情况下，吸附点的hover事件会被父图元截胡，导致原先的hoverEnterEvent()无法接收到hover件***/
/**********在本处理方法中，为了使吸附点能够接收到hover事件，需自定义事件************/
    void my_hoverEnterEvent(QGraphicsSceneHoverEvent *event);   //吸附点高亮
    void my_hoverLeaveEvent(QGraphicsSceneHoverEvent *event);   //取消吸附点高亮

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

signals:
    void arrowPress(Adsorption_point *adsPoint);    //吸附点被press，向外广播该吸附点指针，以准备绘制arrow
    void arrowMove(QPointF arrow_movingPoint);      //发出的坐标应相对于scene坐标系
    void arrowRelease(QPointF arrow_releasePoint);  //发出的坐标应相对于scene坐标系
};

#endif // ADSORPTION_POINT_H
