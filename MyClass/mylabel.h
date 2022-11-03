#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    enum myLabType  //定义枚举变量
    {
        initial_end_item = 0,   //圆角矩形
        procedure_item,         //矩形
        judge_item              //菱形
    };
    enum myLabType mylabtype;   //声明枚举变量

    MyLabel(QWidget *parent = 0);
    ~MyLabel();

protected:
    void mouseReleaseEvent(QMouseEvent *ev) Q_DECL_OVERRIDE;    //鼠标抬起事件，即点击了某幅图片

signals:
    void myLabClick(enum myLabType mylabtype);  //某幅图片被点击，向外广播它的类型，由scene接收

};


#endif // MYLABEL_H
