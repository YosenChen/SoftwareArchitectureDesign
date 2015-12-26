#ifndef CIRCULAR_Q_H
#define CIRCULAR_Q_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef char      BOOL;
#define true      1
#define false     0

/*********************** CircularQ *********************************/

struct CircularQ
{
//member variables
    int mCap;
    int *mpData;
    int mEnd; //new position to be pushed, it's equal to current size
    int mStart; //the position of first element
    //size = 
    //    if mEnd>mStart:  size = (mEnd-1)-mStart+1 = mEnd-mStart
    //    if mEnd<mStart:  size = (mEnd-1+mCap)-mStart+1 = mEnd-mStart+mCap,
    //    if mEnd==mStart:
    //        if empty: size = 0;
    //        otherwise: size = mCap;
    BOOL mIsEmpty;
    //when mEnd == mStart, there are 2 possibilities, one is empty, another is full. so we need a flag to indicate

//member functions
//operation APIs
    BOOL (*enQ) (struct CircularQ* _this, int ele);
    BOOL (*deQ) (struct CircularQ* _this, int* ele);
//query APIs
    int (*getSize) (struct CircularQ* _this);
    int (*getCapacity) (struct CircularQ* _this);
    BOOL (*isFull) (struct CircularQ* _this);
    BOOL (*isEmpty) (struct CircularQ* _this);

};


//query APIs
int CircularQ_getSize(struct CircularQ* _this);
int CircularQ_getCapacity(struct CircularQ* _this);
BOOL CircularQ_isFull(struct CircularQ* _this);
BOOL CircularQ_isEmpty(struct CircularQ* _this);

//operation APIs
BOOL CircularQ_enQ(struct CircularQ* _this, int ele);
BOOL CircularQ_deQ(struct CircularQ* _this, int* ele);

//create, destroy APIs
void CircularQ_ctor(struct CircularQ* _this, int cap);
void CircularQ_dtor(struct CircularQ* _this);
struct CircularQ* CircularQ_operator_new(int cap);
void CircularQ_operator_delete (struct CircularQ* _this);




#endif