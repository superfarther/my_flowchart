#ifndef MY_GRAPHICSSCENE_H
#define MY_GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QTextBrowser>
#include <QtDebug>
#include <iostream>
#include <iomanip>
#include "MyGraphicsItem/initial_end_item.h"
#include "MyGraphicsItem/procedure_item.h"
#include "MyGraphicsItem/judge_item.h"
#include "MyClass/mylabel.h"
#include "MyGraphicsItem/arrow_item.h"
#include "MyGraphicsItem/myitem_base.h"
#include "my_stack.h"

class My_graphicsscene : public QGraphicsScene
{

    Q_OBJECT

public:
    My_graphicsscene(QObject *parent = 0);
    ~My_graphicsscene();

    void connectScene_adsPoint(My_graphicsscene* scene, Myitem_base* item); 

    void flowchartLineArize(Myitem_base* chartStartItem, Myitem_base* chartEndItem); 
    void ScanFlowChart(QString* Ccode, Myitem_base* item, int indent); 

public slots:
    void on_myLabClick(MyLabel::myLabType clickedLabType); 

    void on_arrowPress(Adsorption_point *startAdsPoint); 
    void on_arrowMove(QPointF arrow_movingPoint, Adsorption_point *startAdsPoint); 
    void on_arrowRelease(QPointF arrow_ReleasePoint);

    void flowChart_C(); 

private:
    ArrowItem* drawingArrow = nullptr; 
    Myitem_base* highLightingItem = nullptr; 
    Adsorption_point* highLightingAdsPoint = nullptr; 

    Myitem_base* chartStartItem = nullptr; 
    Myitem_base* chartEndItem = nullptr; 

    MyStack stack;
};

#endif 
