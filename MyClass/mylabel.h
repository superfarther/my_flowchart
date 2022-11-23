#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    enum myLabType 
    {
        initial_end_item = 0, 
        procedure_item, 
        judge_item 
    };
    enum myLabType mylabtype; 

    MyLabel(QWidget *parent = 0);
    ~MyLabel();

protected:
    void mouseReleaseEvent(QMouseEvent *ev) Q_DECL_OVERRIDE; 

signals:
    void myLabClick(enum myLabType mylabtype); 

};


#endif 
