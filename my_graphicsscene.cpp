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
            initial_end_item->setPos(300, 300); //在scene坐标系中
            this->addItem(initial_end_item);
            connectScene_adsPoint(this, initial_end_item);
        }
        break;

        case MyLabel::procedure_item:
        {
            Procedure_item *procedure_item = new Procedure_item();
            procedure_item->setPos(400, 400); //在scene坐标系中
            this->addItem(procedure_item);
            connectScene_adsPoint(this, procedure_item);
        }
        break;

        case MyLabel::judge_item:
        {
            Judge_item *judge_item = new Judge_item();
            judge_item->setPos(500, 500); //在scene坐标系中
            this->addItem(judge_item);
            connectScene_adsPoint(this, judge_item);
        }
        break;

        default: break;
    }
}

void My_graphicsscene::on_arrowPress(Adsorption_point *adsPoint)
{
    drawingArrow = new ArrowItem();
    drawingArrow->setStartPoint(adsPoint->getPos());

    this->addItem(drawingArrow);
}

void My_graphicsscene::on_arrowMove(QPointF arrow_movingPoint)
{
    if(drawingArrow)
    {
        QLineF linef(drawingArrow->getStartPoint(), arrow_movingPoint);
        drawingArrow->setLine(linef);

        this->update(drawingArrow->boundingRect());
    }
}

void My_graphicsscene::on_arrowRelease(QPointF arrow_ReleasePoint)
{
    if(drawingArrow)
    {
        drawingArrow->setEndPoint(arrow_ReleasePoint);
        drawingArrow = nullptr; //绘制完成
    }
}
