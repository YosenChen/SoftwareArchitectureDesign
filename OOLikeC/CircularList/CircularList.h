#ifndef CIRCULARLIST_H
#define CIRCULARLIST_H

#include "CircularQ.h"


/*********************** CircularList *********************************/
// inherit from CircularQ, it adds stack operations

struct CircularList
{
//inherit from CircularQ
    struct CircularQ _base;

//member variables
    
//member funcitons
    BOOL (*push) (struct CircularList* _this, int ele);
    BOOL (*pop) (struct CircularList* _this, int* ele);
};


//operation APIs
BOOL CircularList_pop(struct CircularList* _this, int* ele);
BOOL CircularList_push(struct CircularList* _this, int ele);

//create, destroy APIs
void CircularList_ctor(struct CircularList* _this, int cap);
void CircularList_dtor(struct CircularList* _this);
struct CircularList* CircularList_operator_new(int cap);
void CircularList_operator_delete (struct CircularList* _this);

#endif