#include "my_graphicsscene.h"
#include <QLineF>

My_graphicsscene::My_graphicsscene(QObject *parent) : QGraphicsScene(parent)
{

}

My_graphicsscene::~My_graphicsscene()
{

}

void My_graphicsscene::connectScene_adsPoint(My_graphicsscene *scene, Myitem_base *item)
{
     connect(item->getTop_adsPoint(), &Adsorption_point::arrowPress, scene, &My_graphicsscene::on_arrowPress);
    connect(item->getTop_adsPoint(), &Adsorption_point::arrowMove, scene, &My_graphicsscene::on_arrowMove);
    connect(item->getTop_adsPoint(), &Adsorption_point::arrowRelease, scene, &My_graphicsscene::on_arrowRelease);
     connect(item->getBelow_adsPoint(), &Adsorption_point::arrowPress, scene, &My_graphicsscene::on_arrowPress);
    connect(item->getBelow_adsPoint(), &Adsorption_point::arrowMove, scene, &My_graphicsscene::on_arrowMove);
    connect(item->getBelow_adsPoint(), &Adsorption_point::arrowRelease, scene, &My_graphicsscene::on_arrowRelease);
     connect(item->getLeft_adsPoint(), &Adsorption_point::arrowPress, scene, &My_graphicsscene::on_arrowPress);
    connect(item->getLeft_adsPoint(), &Adsorption_point::arrowMove, scene, &My_graphicsscene::on_arrowMove);
    connect(item->getLeft_adsPoint(), &Adsorption_point::arrowRelease, scene, &My_graphicsscene::on_arrowRelease);
     connect(item->getRight_adsPoint(), &Adsorption_point::arrowPress, scene, &My_graphicsscene::on_arrowPress);
    connect(item->getRight_adsPoint(), &Adsorption_point::arrowMove, scene, &My_graphicsscene::on_arrowMove);
    connect(item->getRight_adsPoint(), &Adsorption_point::arrowRelease, scene, &My_graphicsscene::on_arrowRelease);
}

void My_graphicsscene::on_myLabClick(MyLabel::myLabType clickedLabType)
{
    switch (clickedLabType){
        case MyLabel::initial_end_item:
        {
            Initial_end_item *initial_end_item = new Initial_end_item();
             this->addItem(initial_end_item);
            connectScene_adsPoint(this, initial_end_item);
        }
        break;

        case MyLabel::procedure_item:
        {
            Procedure_item *procedure_item = new Procedure_item();
             this->addItem(procedure_item);
            connectScene_adsPoint(this, procedure_item);
        }
        break;

        case MyLabel::judge_item:
        {
            Judge_item *judge_item = new Judge_item();
             this->addItem(judge_item);
            connectScene_adsPoint(this, judge_item);
        }
        break;

        default: break;
    }
}

void My_graphicsscene::on_arrowPress(Adsorption_point *startAdsPoint)
{
     drawingArrow = new ArrowItem();
    drawingArrow->setStartPoint(startAdsPoint->getPos());
    drawingArrow->setTailToAdsPoint(startAdsPoint);
    if(typeid(*(startAdsPoint->parentItem())) != typeid(Judge_item))
    {
        drawingArrow->setLogicType(ArrowItem::commonType);  //若item为菱形框，则需在连接好箭头后，手动确定箭头的逻辑类型(T or F)
    }
    this->addItem(drawingArrow);
     startAdsPoint->setToArrow(drawingArrow);
    startAdsPoint->setToArrowWhich(Adsorption_point::arrowTail);
}

void My_graphicsscene::on_arrowMove(QPointF arrow_movingPoint, Adsorption_point *startAdsPoint)
{
    if(drawingArrow)
    {
        QLineF linef(drawingArrow->getStartPoint(), arrow_movingPoint);
        drawingArrow->setLine(linef);

        QList<QGraphicsItem*> list = this->items(arrow_movingPoint);  
        Myitem_base* startItem = dynamic_cast<Myitem_base*> (startAdsPoint->parentItem());
        list.removeAll(startItem);
        list.removeAll(startItem->getTop_adsPoint());
        list.removeAll(startItem->getBelow_adsPoint());
        list.removeAll(startItem->getLeft_adsPoint());
        list.removeAll(startItem->getRight_adsPoint());
         if(highLightingItem)
        {
            qreal itemLenth = highLightingItem->getLenth();
            qreal itemwidth = highLightingItem->getWidth();
            QRectF recf(highLightingItem->scenePos().x()-itemLenth/2, highLightingItem->scenePos().y()-itemwidth/2,itemLenth, itemwidth);
            QPointF sceneMapToItem = arrow_movingPoint - highLightingItem->getCentral_point();
             if(recf.contains(arrow_movingPoint))
            {
                highLightingItem->my_hoverEnterEvent();
                 highLightingAdsPoint = highLightingItem->whichAdsPoint(sceneMapToItem);
                 if(highLightingAdsPoint)
                {
                    highLightingAdsPoint->my_hoverEnterEvent();
                }
                 else
                {
                    highLightingItem->getTop_adsPoint()->my_hoverLeaveEvent();
                    highLightingItem->getLeft_adsPoint()->my_hoverLeaveEvent();
                    highLightingItem->getBelow_adsPoint()->my_hoverLeaveEvent();
                    highLightingItem->getRight_adsPoint()->my_hoverLeaveEvent();
                }
            }
             else
            {
                highLightingItem->my_hoverLeaveEvent();
                highLightingAdsPoint = nullptr;
                highLightingItem = nullptr;
            }
        }
         else
        {
            highLightingAdsPoint = nullptr;
                if(list.length() > 1 && (typeid(*list.at(1)) == typeid(Initial_end_item) || typeid(*list.at(1)) == typeid(Judge_item) || typeid(*list.at(1)) == typeid(Procedure_item)))
            {
                highLightingItem = dynamic_cast<Myitem_base*> (list.at(1));
                highLightingItem->my_hoverEnterEvent();
            }
        }

    }

}

void My_graphicsscene::on_arrowRelease(QPointF arrow_ReleasePoint)
{
    if(drawingArrow)
    {
         if(highLightingAdsPoint)
        {
             QLineF linef(drawingArrow->getStartPoint(), highLightingAdsPoint->getPos());
            drawingArrow->setEndPoint(highLightingAdsPoint->getPos());
            drawingArrow->setClusterToAdsPoint(highLightingAdsPoint);
            drawingArrow->identifyPaintingType();   //标识箭头绘制类型
            drawingArrow->identifyBrokenLinePath(); //标识折线路径（如果是折线的话）
            drawingArrow->setLine(linef);
             highLightingAdsPoint->setToArrow(drawingArrow);
            highLightingAdsPoint->setToArrowWhich(Adsorption_point::arrowCluster);
             Myitem_base* startItem = dynamic_cast<Myitem_base*>(drawingArrow->getTailToAdsPoint()->parentItem());
            if(typeid(*startItem) != typeid(Judge_item))
            {
                startItem->setNextItem(dynamic_cast<Myitem_base*>(highLightingAdsPoint->parentItem())); 
            }
        }
         else
        {
           drawingArrow->setEndPoint(arrow_ReleasePoint);
        }
        drawingArrow->paintArrowCluster();
         highLightingItem = nullptr;
        highLightingAdsPoint = nullptr;
        drawingArrow = nullptr;
    }
}
