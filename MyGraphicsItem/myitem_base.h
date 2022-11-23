#ifndef MYITEM_BASE_H
#define MYITEM_BASE_H

#include <QAbstractGraphicsShapeItem>
#include <QPen>
#include <QPainter>
#include <QGraphicsScene>
#include <QTextBlockFormat>
#include <QTextCursor>
#include <QtDebug>
#include "MyPoint/adsorption_point.h"
#include "arrow_item.h"

class Myitem_base : public QAbstractGraphicsShapeItem
{

public:
    
    typedef enum nextItemType 
    {
        noMatter = 0, 
        nextTrueType,   
        nextFalseType
    }nextItemType;
    
    Myitem_base(QGraphicsItem *parent = 0);
    ~Myitem_base();

    qreal getLenth() const;
    void setLenth(const qreal &value);

    qreal getWidth() const;
    void setWidth(const qreal &value);

    QPointF getCentral_point();
 

    Adsorption_point *getTop_adsPoint() const;
    Adsorption_point *getBelow_adsPoint() const;
    Adsorption_point *getLeft_adsPoint() const;
    Adsorption_point *getRight_adsPoint() const;
    void initialize_adsPoint(); 
    void update_adsPoint(); 
    void show_adsPoint(); 
    void disappear_adsPoint(); 
    Adsorption_point* whichAdsPoint(QPointF eventPos); 

    void my_hoverEnterEvent(); 
    void my_hoverLeaveEvent(); 

    virtual void setNextItem(Myitem_base* nextItem, ArrowItem* arrow = nullptr) = 0; 
    virtual Myitem_base* getNextItem(nextItemType whichType) = 0;

    void initialize_text();

    QGraphicsTextItem *getText() const;

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

private:
    qreal lenth; 
    qreal width; 

    QPointF central_point; 

    Adsorption_point *top_adsPoint;
    Adsorption_point *below_adsPoint;
    Adsorption_point *left_adsPoint; 
    Adsorption_point *right_adsPoint; 

    QGraphicsTextItem* text;
};

#endif 
