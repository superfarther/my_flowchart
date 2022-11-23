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
 
            if(chartStartItem == nullptr){
                chartStartItem = initial_end_item;
                qDebug("该图元是起始图元");
            }
            else{
                chartEndItem = initial_end_item;
                qDebug("该图元是终止图元");
            }

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
        drawingArrow->setLogicType(ArrowItem::commonType); 
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
            drawingArrow->identifyPaintingType(); 
            drawingArrow->identifyBrokenLinePath(); 
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

void My_graphicsscene::flowchartLineArize(Myitem_base* chartStartItem, Myitem_base* chartEndItem)
{   
    stack.clearStack(); 
    Myitem_base* item = chartStartItem;
    while(item != chartEndItem){
 
        if(typeid(*item) == typeid(Initial_end_item)){
            qDebug("\n开始线性化!");
            item = item->getNextItem(Myitem_base::noMatter);
        }

 
        else if(typeid(*item) == typeid(Procedure_item)){
            Procedure_item* procItem = dynamic_cast<Procedure_item*>(item); 
 
            if(procItem->getLoopLimitType() == Procedure_item::noType){
                ArrowItem* arrow = procItem->getLeft_adsPoint()->getToArrow(); 
 
                if(procItem->getLeft_adsPoint()->getToArrowWhich() == Adsorption_point::arrowTail){
                    Myitem_base* toItem = dynamic_cast<Myitem_base*>(arrow->getClusterToAdsPoint()->parentItem()); 
                    if(typeid(*toItem) == typeid(Judge_item) && toItem->getLeft_adsPoint()->getToArrow() == arrow){
                        procItem->setLoopLimitType(Procedure_item::while_below); 
                        qDebug("设置矩形为while下界");
                    }
                }
 
                else if(procItem->getLeft_adsPoint()->getToArrowWhich() == Adsorption_point::arrowCluster){
                    Myitem_base* toItem = dynamic_cast<Myitem_base*>(arrow->getTailToAdsPoint()->parentItem()); 
                    if(typeid(*toItem) == typeid(Judge_item) && toItem->getLeft_adsPoint()->getToArrow() == arrow){
                        procItem->setLoopLimitType(Procedure_item::doWhile_up); 
                        qDebug("设置矩形为do-while上界");
                    }
                    else if(typeid(*toItem) == typeid(Procedure_item) && toItem->getBelow_adsPoint()->getToArrow() == arrow){
                        procItem->setLoopLimitType(Procedure_item::if_else_join); 
                        qDebug("设置矩形为分支判断的汇点");
                    }
                }
 
                else{
                    procItem->setLoopLimitType(Procedure_item::Sequential);
                    qDebug("设置矩形为顺序型");
                }

 
                if(procItem->getLoopLimitType() == Procedure_item::if_else_join){
                    item = stack.pop();
                }
                else if(procItem->getLoopLimitType() == Procedure_item::while_below
                        || procItem->getLoopLimitType() == Procedure_item::doWhile_up
                        || procItem->getLoopLimitType() == Procedure_item::Sequential)
                {
                    item = item->getNextItem(Myitem_base::noMatter);
                }
                else{
                    qDebug("error: my_graphicsscene - 249");
                    exit(-1);
                }
            }
 
            else if(procItem->getLoopLimitType() ==Procedure_item::if_else_join){
                item = item->getNextItem(Myitem_base::noMatter);
            }
        }

 
        else if(typeid(*item) == typeid(Judge_item)){
            Judge_item* judgeItem = dynamic_cast<Judge_item*>(item); 
 
            if(judgeItem->getLoopLimitType() == Judge_item::noType){
                ArrowItem* arrow = judgeItem->getLeft_adsPoint()->getToArrow(); 
 
                if(judgeItem->getLeft_adsPoint()->getToArrowWhich() == Adsorption_point::arrowTail){
                    Myitem_base* toItem = dynamic_cast<Myitem_base*>(arrow->getClusterToAdsPoint()->parentItem()); 
                    if(typeid(*toItem) == typeid(Procedure_item) && toItem->getLeft_adsPoint()->getToArrow() == arrow){
                        judgeItem->setLoopLimitType(Judge_item::doWhile_below); 
                        qDebug("设置菱形为do-while下界");
                    }
                    else if(typeid(*toItem) == typeid(Procedure_item) && toItem->getTop_adsPoint()->getToArrow() == arrow){
                        judgeItem->setLoopLimitType(Judge_item::noloop); 
                        qDebug("设置菱形为分支判断");
                    }
                }
 
                else if(judgeItem->getLeft_adsPoint()->getToArrowWhich() == Adsorption_point::arrowCluster){
                    Myitem_base* toItem = dynamic_cast<Myitem_base*>(arrow->getTailToAdsPoint()->parentItem()); 
                    if(typeid(*toItem) == typeid(Procedure_item) && toItem->getLeft_adsPoint()->getToArrow() == arrow){
                        judgeItem->setLoopLimitType(Judge_item::while_up); 
                        qDebug("设置菱形为while上界");
                    }
                }

 
                if(judgeItem->getLoopLimitType() == Judge_item::while_up){
                    item = item->getNextItem(Myitem_base::nextTrueType);
                }
                else if(judgeItem->getLoopLimitType() == Judge_item::doWhile_below){
                    item = item->getNextItem(Myitem_base::nextFalseType);
                }
                else if(judgeItem->getLoopLimitType() == Judge_item::noloop){
                    stack.push(item);
                    item = item->getNextItem(Judge_item::nextTrueType);
                }
                else{
                    qDebug("error: my_graphicsscene - 296");
                    system("pause");
                }
            }
 
            else if(judgeItem->getLoopLimitType() == Judge_item::while_up
                    || judgeItem->getLoopLimitType() == Judge_item::noloop)
            {
                item = item->getNextItem(Myitem_base::nextFalseType);
            }
            else {
                qDebug("error: my_graphicsscene - 306");
                exit(-1);
            }
        }
    }
    qDebug("线性化完成!");
    return;
}

 
QString generateIndent(int indent){
    QString string;
    for(int i = 0; i < 4*indent; i++){
        string.append(" ");
    }
    return string;
}

void My_graphicsscene::ScanFlowChart(QString* Ccode, Myitem_base* item, int indent)
{
 
    if(typeid(*item) == typeid(Initial_end_item)){
        if(item == chartStartItem){
            Ccode->append("int main(){\n");
            qDebug() << "开始图元 int main(){";
            ScanFlowChart(Ccode, item->getNextItem(Myitem_base::noMatter), ++indent);
 
        }
        else if(item == chartEndItem){
            qDebug() << "结束图元 }";
            Ccode->append(generateIndent(1)+"return 0;"+"\n}");
 
        }
        return;
    }
 
    else if(typeid(*item) == typeid(Procedure_item)){
        Procedure_item* procItem = dynamic_cast<Procedure_item*>(item); 
        switch(procItem->getLoopLimitType()){
            case Procedure_item::if_else_join:
            {
 
                if(item == stack.getTop()){
                    stack.pop();
                    indent--;
                    Ccode->append(generateIndent(indent)+"}\n"+generateIndent(indent)+item->getText()->toPlainText()+"\n");
                    qDebug() << "从F分支进入汇点 矩形" << item->getText()->toPlainText();
                    ScanFlowChart(Ccode, item->getNextItem(Myitem_base::noMatter), indent);
 
                }
 
                else if(item != stack.getTop()){
                    stack.push(item);
                    indent--;
                    Ccode->append(generateIndent(indent)+"}\n");
                    qDebug() << "从T分支进入汇点 矩形" << item->getText()->toPlainText();
 
                }
                break;
            }
            case Procedure_item::while_below:
            {
                qDebug() << "while下界矩形" << item->getText()->toPlainText();
                Ccode->append(generateIndent(indent)+item->getText()->toPlainText()+"\n"+generateIndent(indent-1)+"}\n");
                break;
 
            }
            case Procedure_item::doWhile_up:
            {
                Ccode->append(generateIndent(indent)+"do{\n"+generateIndent(indent+1)+item->getText()->toPlainText()+"\n");
                qDebug() << "do-while上界矩形" << item->getText()->toPlainText();
                ScanFlowChart(Ccode, item->getNextItem(Myitem_base::noMatter), ++indent);
                break;
            }
            case Procedure_item::Sequential:
            {
                Ccode->append(generateIndent(indent)+item->getText()->toPlainText()+"\n");
                qDebug() << "顺序型矩形" << item->getText()->toPlainText();
                ScanFlowChart(Ccode, item->getNextItem(Myitem_base::noMatter), indent);
                break;
            }
            default:{
                qDebug() << "error my_graphicsscene - 388";
                system("pause");
                break;
            }
            return;
        }
    }
 
    else if(typeid(*item) == typeid(Judge_item)){
        Judge_item* judgeItem = dynamic_cast<Judge_item*>(item); 
        switch(judgeItem->getLoopLimitType()){
            case Judge_item::while_up:{
                Ccode->append(generateIndent(indent)+"while("+item->getText()->toPlainText()+"){\n");
                qDebug() << "while上界菱形 T分支" << item->getText()->toPlainText();
                ScanFlowChart(Ccode, item->getNextItem(Myitem_base::nextTrueType), ++indent);

                qDebug() << "while上界菱形 F分支" << item->getText()->toPlainText();
                ScanFlowChart(Ccode, item->getNextItem(Myitem_base::nextFalseType), --indent);
                break;
            }
            case Judge_item::doWhile_below:{
                indent--;
                Ccode->append("\n"+generateIndent(indent)+"}while("+item->getText()->toPlainText()+");\n");
                qDebug() << "do-while下界菱形 F分支" << item->getText()->toPlainText();
                ScanFlowChart(Ccode, item->getNextItem(Myitem_base::nextFalseType), indent);
                break;
            }
            case Judge_item::noloop:{
                Ccode->append(generateIndent(indent)+"if("+item->getText()->toPlainText()+"){\n");
                qDebug() << "分支判断菱形 T分支" << item->getText()->toPlainText();
                ScanFlowChart(Ccode, item->getNextItem(Myitem_base::nextTrueType), ++indent);

                indent--;
                Ccode->append(generateIndent(indent)+"else{\n");
                qDebug() << "分支判断菱形 F分支" << item->getText()->toPlainText();
                ScanFlowChart(Ccode, item->getNextItem(Myitem_base::nextFalseType), ++indent);
                break;
            }
            default:{
                qDebug() << "error my_graphicsscene - 427";
                system("pause");
                break;
            }
            return;
        }
    }
}

void My_graphicsscene::flowChart_C()
{
    flowchartLineArize(chartStartItem, chartEndItem);

    QString* Ccode = new QString();
    stack.clearStack();
    qDebug() << "\n开始生成代码";
    ScanFlowChart(Ccode, chartStartItem, 0);

    QTextBrowser* textBrowser = new QTextBrowser();
    textBrowser->setWindowFlags(Qt::Window); 
    textBrowser->setWindowTitle("FlowChart To C");
    textBrowser->setPlainText(*Ccode);
    textBrowser->setGeometry(100,100,400,400);
    textBrowser->show();
}
