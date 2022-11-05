#include "arrowcluster.h"
#include <QPainter>

ArrowCluster::ArrowCluster(QGraphicsItem *parent) : QGraphicsPolygonItem(parent)
{
    this->setBrush(QBrush(Qt::black, Qt::SolidPattern));
}

ArrowCluster::ArrowCluster(QPolygonF polygonFShape, QGraphicsItem *parent) : QGraphicsPolygonItem(polygonFShape, parent)
{
    this->setBrush(QBrush(Qt::black, Qt::SolidPattern));
}

ArrowCluster::~ArrowCluster()
{

}

void ArrowCluster::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    QGraphicsPolygonItem::paint(painter, option, widget);
}
