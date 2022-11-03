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

    void connectScene_adsPoint(My_graphicsscene* scene, Myitem_base* item); //将scene与item的吸附点connect起来，使得点击吸附点能够绘制箭头

public slots:
    void on_myLabClick(MyLabel::myLabType clickedLabType);   //某幅图片被点击，在scene中添加该种图元

    void on_arrowPress(Adsorption_point *adsPoint);          //吸附点被选中，准备绘制箭头
    void on_arrowMove(QPointF arrow_movingPoint);            //箭头跟随光标移动，光标坐标相对于scene坐标系
    void on_arrowRelease(QPointF arrow_ReleasePoint);

private:
    ArrowItem *drawingArrow = nullptr;    //正在绘制中的arrow
};

#endif // MY_GRAPHICSSCENE_H
