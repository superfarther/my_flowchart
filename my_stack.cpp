#include "my_stack.h"

MyStack::MyStack()
{

}

MyStack::~MyStack()
{

}

Myitem_base *MyStack::pop()
{
    if(!isEmpty()){
        top--;
        return array[top+1];
    }
    else {
        return nullptr;
    }
}

void MyStack::push(Myitem_base *item)
{
    if(!isFull()){
        top++;
        array[top] = item;
        return;
    }
}

Myitem_base *MyStack::getTop()
{
    if(!isEmpty()){
        return array[top];
    }
    else {
        return nullptr;
    }
}

bool MyStack::isEmpty()
{
    if(top < 0){
        return true;
    }
    else{
        return false;
    }
}

bool MyStack::isFull()
{
    if(top >= count-1){
        return true;
    }
    else{
        return false;
    }
}

void MyStack::clearStack()
{
    top = -1;
}
