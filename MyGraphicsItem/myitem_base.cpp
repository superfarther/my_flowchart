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

    show_adsPoint(); 
    QAbstractGraphicsShapeItem::hoverEnterEvent(event);
}

void Myitem_base::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QPen pen(Qt::black, 2);
    this->setPen(pen);

    disappear_adsPoint(); 
    QAbstractGraphicsShapeItem::hoverLeaveEvent(event);
}

void Myitem_base::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    Adsorption_point *adsPoint = whichAdsPoint(event->pos());
 
    if(adsPoint)
    {
        adsPoint->my_hoverEnterEvent(event);
    }
 
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
    central_point = this->pos(); 
    update_adsPoint(); 

 
    Adsorption_point::connectArrowWhich toArrowWhich;
 
    toArrowWhich = getTop_adsPoint()->getToArrowWhich();
    if(toArrowWhich != Adsorption_point::noArrow)
    {
        getTop_adsPoint()->getToArrow()->arrowRepaintEvent(getTop_adsPoint()->getPos(), toArrowWhich);
    }
 
    toArrowWhich = getBelow_adsPoint()->getToArrowWhich();
    if(toArrowWhich != Adsorption_point::noArrow)
    {
        getBelow_adsPoint()->getToArrow()->arrowRepaintEvent(getBelow_adsPoint()->getPos(), toArrowWhich);
    }
 
    toArrowWhich = getLeft_adsPoint()->getToArrowWhich();
    if(toArrowWhich != Adsorption_point::noArrow)
    {
        getLeft_adsPoint()->getToArrow()->arrowRepaintEvent(getLeft_adsPoint()->getPos(), toArrowWhich);
    }
 
    toArrowWhich = getRight_adsPoint()->getToArrowWhich();
    if(toArrowWhich != Adsorption_point::noArrow)
    {
        getRight_adsPoint()->getToArrow()->arrowRepaintEvent(getRight_adsPoint()->getPos(), toArrowWhich);
    }

 
    QAbstractGraphicsShapeItem::mouseMoveEvent(event);
}

void Myitem_base::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {

    }

    QAbstractGraphicsShapeItem::mouseDoubleClickEvent(event);
}

QGraphicsTextItem *Myitem_base::getText() const
{
    return text;
}

void Myitem_base::initialize_text()
{
    text = new QGraphicsTextItem(this);
    text->setHtml(QString("<div style='background-color: #FFEBCD;'>") + "" + "</div>");
    text->setTextInteractionFlags(Qt::TextEditorInteraction);
    text->setTextWidth(this->getLenth()-20);
    text->setPos(-lenth/2+10, -width/2); 
 
    QTextBlockFormat format;
    format.setAlignment(Qt::AlignCenter);
    QTextCursor cursor = text->textCursor();
    cursor.select(QTextCursor::Document);
    cursor.mergeBlockFormat(format);
    cursor.clearSelection();
    text->setTextCursor(cursor);
 
    QFont font;
    font.setBold(true);
    font.setFamily("????????????");
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
    QPointF point; 
    qreal radius; 
 
    point.setX(this->pos().x());
    point.setY(this->pos().y() - this->width/2);
    this->top_adsPoint = new Adsorption_point(point, this); 

    radius = top_adsPoint->getRadius();
    this->top_adsPoint->setRect(point.x()-radius, point.y()-radius, 2*radius, 2*radius);
 
    point.setX(this->pos().x());
    point.setY(this->pos().y() + this->width/2);
    this->below_adsPoint = new Adsorption_point(point, this); 

    radius = below_adsPoint->getRadius();
    this->below_adsPoint->setRect(point.x()-radius, point.y()-radius, 2*radius, 2*radius);
 
    point.setX(this->pos().x() - this->lenth/2);
    point.setY(this->pos().y());
    this->left_adsPoint = new Adsorption_point(point, this);

    radius = left_adsPoint->getRadius();
    this->left_adsPoint->setRect(point.x()-radius, point.y()-radius, 2*radius, 2*radius);
 
    point.setX(this->pos().x() + this->lenth/2);
    point.setY(this->pos().y());
    this->right_adsPoint = new Adsorption_point(point, this);

    radius = right_adsPoint->getRadius();
    this->right_adsPoint->setRect(point.x()-radius, point.y()-radius, 2*radius, 2*radius);

    disappear_adsPoint(); 
}

void Myitem_base::update_adsPoint()
{
    QPointF point;
 
    point.setX(this->pos().x());
    point.setY(this->pos().y() - this->width/2);
    this->top_adsPoint->setPos(point);
 
    point.setX(this->pos().x());
    point.setY(this->pos().y() + this->width/2);
    this->below_adsPoint->setPos(point);
 
    point.setX(this->pos().x() - this->lenth/2);
    point.setY(this->pos().y());
    this->left_adsPoint->setPos(point);
 
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
 
    if(mousePosX >= -adsRadius && mousePosX <= adsRadius && mousePosY >= -width/2-adsRadius && mousePosY <= -width/2+adsRadius)
    {
        return this->top_adsPoint;
    }
 
    else if(mousePosX >= -adsRadius && mousePosX <= adsRadius && mousePosY >= width/2-adsRadius && mousePosY <= width/2+adsRadius)
    {
        return this->below_adsPoint;
    }
 
    else if(mousePosX >= -adsRadius-lenth/2 && mousePosX <= adsRadius-lenth/2 && mousePosY >= -adsRadius && mousePosY <= adsRadius)
    {
        return this->left_adsPoint;
    }
 
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

    show_adsPoint(); 
}

void Myitem_base::my_hoverLeaveEvent()
{
    QPen pen(Qt::black, 2);
    this->setPen(pen);

    disappear_adsPoint(); 
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

