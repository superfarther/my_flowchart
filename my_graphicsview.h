#ifndef MY_GRAPHICSVIEW_H
#define MY_GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWidget>

class My_graphicsview : public QGraphicsView
{

    Q_OBJECT

public:
    My_graphicsview(QWidget *parent = 0);
    ~My_graphicsview();
};

#endif // MY_GRAPHICSVIEW_H
