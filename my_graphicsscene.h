#ifndef MY_GRAPHICSSCENE_H
#define MY_GRAPHICSSCENE_H

#include <QGraphicsScene>
#include "MyGraphicsItem/initial_end_item.h"
#include "MyGraphicsItem/procedure_item.h"
#include "MyGraphicsItem/judge_item.h"
#include "MyClass/mylabel.h"
#include "MyGraphicsItem/arrow_item.h"
#include "MyGraphicsItem/myitem_base.h"

class My_graphicsscene : public QGraphicsScene
{

    Q_OBJECT

public:
    My_graphicsscene(QObject *parent = 0);
    ~My_graphicsscene();

    void connectScene_adsPoint(My_graphicsscene* scene, Myitem_base* item);

public slots:
    void on_myLabClick(MyLabel::myLabType clickedLabType);   //某幅图片被点击，在scene中添加该种图元

    void on_arrowPress(Adsorption_point *startAdsPoint);          //吸附点被选中，准备绘制箭头
    void on_arrowMove(QPointF arrow_movingPoint, Adsorption_point *startAdsPoint);            //箭头跟随光标移动，光标坐标相对于scene坐标系
    void on_arrowRelease(QPointF arrow_ReleasePoint);

private:
    ArrowItem* drawingArrow = nullptr;
    Myitem_base* highLightingItem = nullptr;
    Adsorption_point* highLightingAdsPoint = nullptr;
};

#endif
