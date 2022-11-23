#ifndef ARROWCLUSTER_H
#define ARROWCLUSTER_H

#include <QGraphicsPolygonItem>

 
class ArrowCluster : public QGraphicsPolygonItem
{
public:
    ArrowCluster(QGraphicsItem* parent = 0);
    ArrowCluster(QPolygonF polygonFShape, QGraphicsItem* parent = 0);
    ~ArrowCluster();

 
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE;
};

#endif 
