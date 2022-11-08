#include "myitem_base.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>

Myitem_base::Myitem_base(QGraphicsItem *parent): QAbstractGraphicsShapeItem(parent)
{
    this->lenth = 150;
    this->width = 80;

    setAcceptHoverEvents(true);
    setFlags(QGraphicsItem::ItemIsMovable);
    initialize_text();
}

Myitem_base::~Myitem_base()
{

}

void Myitem_base::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QPen pen(Qt::green, 2);
    this->setPen(pen);

    show_adsPoint();    //吸附点可见
    QAbstractGraphicsShapeItem::hoverEnterEvent(event);
}

void Myitem_base::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QPen pen(Qt::black, 2);
    this->setPen(pen);

    disappear_adsPoint();   //吸附点不可见
    QAbstractGraphicsShapeItem::hoverLeaveEvent(event);
}

void Myitem_base::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    Adsorption_point *adsPoint = whichAdsPoint(event->pos());
    //吸附点高亮
    if(adsPoint)
    {
        adsPoint->my_hoverEnterEvent(event);
    }
    //取消所有吸附点高亮
    else
    {
        top_adsPoint->my_hoverLeaveEvent(event);
        below_adsPoint->my_hoverLeaveEvent(event);
        left_adsPoint->my_hoverLeaveEvent(event);
        right_adsPoint->my_hoverLeaveEvent(event);
    }

    QAbstractGraphicsShapeItem::hoverMoveEvent(event);
}

void Myitem_base::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    central_point = this->pos();    //this->pos()默认返回图形中心点坐标，相对于scene坐标系
    update_adsPoint();              //更新吸附点坐标

    //同步移动吸附点连接的箭头
    Adsorption_point::connectArrowWhich toArrowWhich;
    //上吸附点
    toArrowWhich = getTop_adsPoint()->getToArrowWhich();
    if(toArrowWhich != Adsorption_point::noArrow)
    {
        getTop_adsPoint()->getToArrow()->arrowRepaintEvent(getTop_adsPoint()->getPos(), toArrowWhich);
    }
    //下吸附点
    toArrowWhich = getBelow_adsPoint()->getToArrowWhich();
    if(toArrowWhich != Adsorption_point::noArrow)
    {
        getBelow_adsPoint()->getToArrow()->arrowRepaintEvent(getBelow_adsPoint()->getPos(), toArrowWhich);
    }
    //左吸附点
    toArrowWhich = getLeft_adsPoint()->getToArrowWhich();
    if(toArrowWhich != Adsorption_point::noArrow)
    {
        getLeft_adsPoint()->getToArrow()->arrowRepaintEvent(getLeft_adsPoint()->getPos(), toArrowWhich);
    }
    //右吸附点
    toArrowWhich = getRight_adsPoint()->getToArrowWhich();
    if(toArrowWhich != Adsorption_point::noArrow)
    {
        getRight_adsPoint()->getToArrow()->arrowRepaintEvent(getRight_adsPoint()->getPos(), toArrowWhich);
    }

    //qDebug("%f", this->getTop_adsPoint()->QGraphicsItem::pos().x());    Why???
    QAbstractGraphicsShapeItem::mouseMoveEvent(event);
}

void Myitem_base::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {

    }

    QAbstractGraphicsShapeItem::mouseDoubleClickEvent(event);
}

void Myitem_base::initialize_text()
{
    text = new QGraphicsTextItem(this);
    text->setHtml(QString("<div style='background-color: #FFEBCD;'>") + "" + "</div>");
    text->setTextInteractionFlags(Qt::TextEditorInteraction);
    text->setTextWidth(this->getLenth()-20);
    text->setPos(-lenth/2+10, -width/2);   //相对于父图元的坐标
    //文字居中
    QTextBlockFormat format;
    format.setAlignment(Qt::AlignCenter);
    QTextCursor cursor = text->textCursor();
    cursor.select(QTextCursor::Document);
    cursor.mergeBlockFormat(format);
    cursor.clearSelection();
    text->setTextCursor(cursor);
    //设置字体
    QFont font;
    font.setBold(true);
    font.setFamily("微软雅黑");
    font.setPointSize(10);
    text->setFont(font);
}


Adsorption_point *Myitem_base::getRight_adsPoint() const
{
    return right_adsPoint;
}

Adsorption_point *Myitem_base::getLeft_adsPoint() const
{
    return left_adsPoint;
}

Adsorption_point *Myitem_base::getBelow_adsPoint() const
{
    return below_adsPoint;
}

Adsorption_point *Myitem_base::getTop_adsPoint() const
{
    return top_adsPoint;
}

void Myitem_base::initialize_adsPoint()
{
    QPointF point;  //吸附点圆心坐标
    qreal radius;   //吸附点半径
    //上吸附点
    point.setX(this->pos().x());
    point.setY(this->pos().y() - this->width/2);
    this->top_adsPoint = new Adsorption_point(point, this);     //吸附点的父图元是此Item！！！

    radius = top_adsPoint->getRadius();
    this->top_adsPoint->setRect(point.x()-radius, point.y()-radius, 2*radius, 2*radius);
    //下吸附点
    point.setX(this->pos().x());
    point.setY(this->pos().y() + this->width/2);
    this->below_adsPoint = new Adsorption_point(point, this);   //吸附点的父图元是此Item！！！

    radius = below_adsPoint->getRadius();
    this->below_adsPoint->setRect(point.x()-radius, point.y()-radius, 2*radius, 2*radius);
    //左吸附点
    point.setX(this->pos().x() - this->lenth/2);
    point.setY(this->pos().y());
    this->left_adsPoint = new Adsorption_point(point, this);

    radius = left_adsPoint->getRadius();
    this->left_adsPoint->setRect(point.x()-radius, point.y()-radius, 2*radius, 2*radius);
    //右吸附点
    point.setX(this->pos().x() + this->lenth/2);
    point.setY(this->pos().y());
    this->right_adsPoint = new Adsorption_point(point, this);

    radius = right_adsPoint->getRadius();
    this->right_adsPoint->setRect(point.x()-radius, point.y()-radius, 2*radius, 2*radius);

    disappear_adsPoint();   //初始产生图元时，设置吸附点不可见
}

void Myitem_base::update_adsPoint()
{
    QPointF point;
    //上吸附点
    point.setX(this->pos().x());
    point.setY(this->pos().y() - this->width/2);
    this->top_adsPoint->setPos(point);
    //下吸附点
    point.setX(this->pos().x());
    point.setY(this->pos().y() + this->width/2);
    this->below_adsPoint->setPos(point);
    //左吸附点
    point.setX(this->pos().x() - this->lenth/2);
    point.setY(this->pos().y());
    this->left_adsPoint->setPos(point);
    //右吸附点
    point.setX(this->pos().x() + this->lenth/2);
    point.setY(this->pos().y());
    this->right_adsPoint->setPos(point);
}

void Myitem_base::show_adsPoint()
{
    this->top_adsPoint->setVisible(true);
    this->below_adsPoint->setVisible(true);
    this->left_adsPoint->setVisible(true);
    this->right_adsPoint->setVisible(true);
}

void Myitem_base::disappear_adsPoint()
{
    this->top_adsPoint->setVisible(false);
    this->below_adsPoint->setVisible(false);
    this->left_adsPoint->setVisible(false);
    this->right_adsPoint->setVisible(false);
}

Adsorption_point *Myitem_base::whichAdsPoint(QPointF eventPos)
{
    qreal mousePosX = eventPos.x();
    qreal mousePosY = eventPos.y();
    qreal adsRadius = this->getTop_adsPoint()->getRadius();
    //上吸附点
    if(mousePosX >= -adsRadius && mousePosX <= adsRadius && mousePosY >= -width/2-adsRadius && mousePosY <= -width/2+adsRadius)
    {
        return this->top_adsPoint;
    }
    //下吸附点
    else if(mousePosX >= -adsRadius && mousePosX <= adsRadius && mousePosY >= width/2-adsRadius && mousePosY <= width/2+adsRadius)
    {
        return this->below_adsPoint;
    }
    //左吸附点
    else if(mousePosX >= -adsRadius-lenth/2 && mousePosX <= adsRadius-lenth/2 && mousePosY >= -adsRadius && mousePosY <= adsRadius)
    {
        return this->left_adsPoint;
    }
    //右吸附点
    else if(mousePosX >= -adsRadius+lenth/2 && mousePosX <= adsRadius+lenth/2 && mousePosY >= -adsRadius && mousePosY <= adsRadius)
    {
        return this->right_adsPoint;
    }
    else
        return nullptr;
}

void Myitem_base::my_hoverEnterEvent()
{
    QPen pen(Qt::green, 2);
    this->setPen(pen);

    show_adsPoint();    //吸附点可见
}

void Myitem_base::my_hoverLeaveEvent()
{
    QPen pen(Qt::black, 2);
    this->setPen(pen);

    disappear_adsPoint();   //吸附点不可见
}

QPointF Myitem_base::getCentral_point()
{
    return central_point;
}



qreal Myitem_base::getWidth() const
{
    return width;
}

void Myitem_base::setWidth(const qreal &value)
{
    width = value;
}

void Myitem_base::setLenth(const qreal &value)
{
    lenth = value;
}

qreal Myitem_base::getLenth() const
{
    return lenth;
}

