#ifndef ARROWCLUSTER_H
#define ARROWCLUSTER_H

#include <QGraphicsPolygonItem>

//箭簇
class ArrowCluster : public QGraphicsPolygonItem
{
public:
    ArrowCluster(QGraphicsItem* parent = 0);
    ArrowCluster(QPolygonF polygonFShape, QGraphicsItem* parent = 0);
    ~ArrowCluster();

    //重写paint以设置反走样和填充样式
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE;
};

#endif // ARROWCLUSTER_H
