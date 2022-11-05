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
    //上吸附点
    connect(item->getTop_adsPoint(), &Adsorption_point::arrowPress, scene, &My_graphicsscene::on_arrowPress);
    connect(item->getTop_adsPoint(), &Adsorption_point::arrowMove, scene, &My_graphicsscene::on_arrowMove);
    connect(item->getTop_adsPoint(), &Adsorption_point::arrowRelease, scene, &My_graphicsscene::on_arrowRelease);
    //下吸附点
    connect(item->getBelow_adsPoint(), &Adsorption_point::arrowPress, scene, &My_graphicsscene::on_arrowPress);
    connect(item->getBelow_adsPoint(), &Adsorption_point::arrowMove, scene, &My_graphicsscene::on_arrowMove);
    connect(item->getBelow_adsPoint(), &Adsorption_point::arrowRelease, scene, &My_graphicsscene::on_arrowRelease);
    //下吸附点
    //左吸附点
    connect(item->getLeft_adsPoint(), &Adsorption_point::arrowPress, scene, &My_graphicsscene::on_arrowPress);
    connect(item->getLeft_adsPoint(), &Adsorption_point::arrowMove, scene, &My_graphicsscene::on_arrowMove);
    connect(item->getLeft_adsPoint(), &Adsorption_point::arrowRelease, scene, &My_graphicsscene::on_arrowRelease);
    //右吸附点
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
            //initial_end_item->setPos(300, 300); //在scene坐标系中。若不注释掉这句，会产生一个BUG
            this->addItem(initial_end_item);
            connectScene_adsPoint(this, initial_end_item);
        }
        break;

        case MyLabel::procedure_item:
        {
            Procedure_item *procedure_item = new Procedure_item();
            //procedure_item->setPos(400, 400); //在scene坐标系中
            this->addItem(procedure_item);
            connectScene_adsPoint(this, procedure_item);
        }
        break;

        case MyLabel::judge_item:
        {
            Judge_item *judge_item = new Judge_item();
            //judge_item->setPos(500, 500); //在scene坐标系中
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

        //获取光标下的item列表，并remove掉引出drawingArrow的吸附点与item，再排除掉光标下的所有箭头(与箭簇)
        //QList<QGraphicsItem*> list = this->collidingItems(drawingArrow);
        QList<QGraphicsItem*> list = this->items(arrow_movingPoint);    //获取光标下的item列表
        Myitem_base* startItem = dynamic_cast<Myitem_base*> (startAdsPoint->parentItem());  //引出箭头的item
        list.removeAll(startItem);
        list.removeAll(startItem->getTop_adsPoint());
        list.removeAll(startItem->getBelow_adsPoint());
        list.removeAll(startItem->getLeft_adsPoint());
        list.removeAll(startItem->getRight_adsPoint());
        //若当前存在高亮item
        if(highLightingItem)
        {
            qreal itemLenth = highLightingItem->getLenth();
            qreal itemwidth = highLightingItem->getWidth();
            QRectF recf(highLightingItem->scenePos().x()-itemLenth/2, highLightingItem->scenePos().y()-itemwidth/2,itemLenth, itemwidth);   //高亮item的包围矩形
            QPointF sceneMapToItem = arrow_movingPoint - highLightingItem->getCentral_point();  //光标相对于高亮item坐标系的坐标
            //若光标在高亮item上方
            if(recf.contains(arrow_movingPoint))
            {
                highLightingItem->my_hoverEnterEvent();
                //判断有无需要高亮的吸附点
                highLightingAdsPoint = highLightingItem->whichAdsPoint(sceneMapToItem);
                //若有需要高亮的吸附点
                if(highLightingAdsPoint)
                {
                    highLightingAdsPoint->my_hoverEnterEvent();
                }
                //否则，高亮item的所有吸附点取消高亮
                else
                {
                    highLightingItem->getTop_adsPoint()->my_hoverLeaveEvent();
                    highLightingItem->getLeft_adsPoint()->my_hoverLeaveEvent();
                    highLightingItem->getBelow_adsPoint()->my_hoverLeaveEvent();
                    highLightingItem->getRight_adsPoint()->my_hoverLeaveEvent();
                }
            }
            //光标不在高亮item上方
            else
            {
                highLightingItem->my_hoverLeaveEvent();
                highLightingAdsPoint = nullptr;
                highLightingItem = nullptr;
            }
        }
        //若当前不存在高亮item，判断当前光标下方是否有item需要被高亮
        else
        {
            highLightingAdsPoint = nullptr;
            //drawingArrow（即正在移动的箭头本身）可能是item[0]
            //当光标下只有箭头时，item[1]应该是箭头，此时不能进入if语句块内
            //当光标下既有箭头，也有item时，item[1]应该是最上方的MyItem_base
            if(list.length() > 1 && typeid(*list.at(1)) != typeid(ArrowItem) && typeid(*list.at(1)) != typeid(ArrowCluster))    //排除掉所有箭头与箭簇
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
        //如果在arrow在吸附点上结束绘制，arrow被吸附
        if(highLightingAdsPoint)
        {
            QLineF linef(drawingArrow->getStartPoint(), highLightingAdsPoint->getPos());
            drawingArrow->setLine(linef);
            drawingArrow->setEndPoint(highLightingAdsPoint->getPos());
            drawingArrow->setClusterToAdsPoint(highLightingAdsPoint);

            highLightingAdsPoint->setToArrow(drawingArrow);
            highLightingAdsPoint->setToArrowWhich(Adsorption_point::arrowCluster);
        }
        //否则
        else
        {
           drawingArrow->setEndPoint(arrow_ReleasePoint);
        }
        drawingArrow->paintArrowCluster();  //绘制箭簇
        //绘制完成
        highLightingItem = nullptr;
        highLightingAdsPoint = nullptr;
        drawingArrow = nullptr;
    }
}
