#ifndef MY_STACK_H
#define MY_STACK_H

#include "MyGraphicsItem/myitem_base.h"

class MyStack
{
public:
    MyStack();
    ~MyStack();

    Myitem_base* pop();
    void push(Myitem_base* item);
    Myitem_base* getTop();
    bool isEmpty();
    bool isFull();
    void clearStack();

private:
    Myitem_base* array[15];
    int top = -1; 
    int count = 15; 
};

#endif 
