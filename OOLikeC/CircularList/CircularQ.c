#include "CircularQ.h"

BOOL CircularQ_enQ(struct CircularQ* _this, int ele)
{
    if (_this->isFull(_this)) return false;
    _this->mpData[_this->mEnd] = ele;
    _this->mEnd = (_this->mEnd+1)%(_this->mCap);
    _this->mIsEmpty = false;
    return true;
}
BOOL CircularQ_deQ(struct CircularQ* _this, int* ele)
{
    if (_this->isEmpty(_this)) return false;
    *ele = _this->mpData[_this->mStart];
    _this->mStart = (_this->mStart+1)%(_this->mCap);
    if (_this->mStart == _this->mEnd) _this->mIsEmpty = true;
    return true;
}
int CircularQ_getSize(struct CircularQ* _this)
{
    //size = 
    //    if mEnd>mStart:  size = (mEnd-1)-mStart+1 = mEnd-mStart
    //    if mEnd<mStart:  size = (mEnd-1+mCap)-mStart+1 = mEnd-mStart+mCap,
    //    if mEnd==mStart:
    //        if empty: size = 0;
    //        otherwise: size = mCap;
    printf("CircularQ_getSize: mEnd = %d, mStart = %d, mCap = %d\n", _this->mEnd, _this->mStart, _this->mCap);

    if (_this->mEnd > _this->mStart) return _this->mEnd - _this->mStart;
    else if (_this->mEnd < _this->mStart) return _this->mEnd - _this->mStart + _this->mCap;
	else //(_this->mEnd == _this->mStart)
        if (_this->mIsEmpty) return 0;
        else return _this->mCap;
}
int CircularQ_getCapacity(struct CircularQ* _this)
{
    return _this->mCap;
}
BOOL CircularQ_isFull(struct CircularQ* _this)
{
    return (_this->mEnd == _this->mStart) && (!_this->mIsEmpty);
}
BOOL CircularQ_isEmpty(struct CircularQ* _this)
{
    return (_this->mIsEmpty);
}

void CircularQ_ctor(struct CircularQ* _this, int cap)
{
//member variables
    _this->mCap = cap;
    _this->mEnd = _this->mStart = 0;
    _this->mIsEmpty = true;
    _this->mpData = (int*)malloc(sizeof(int)*cap);
    memset(_this->mpData, 0x00, sizeof(int)*cap);
//member functions
    _this->enQ = CircularQ_enQ;
    _this->deQ = CircularQ_deQ;
    _this->getSize = CircularQ_getSize;
    _this->isFull = CircularQ_isFull;
    _this->isEmpty = CircularQ_isEmpty;
}

void CircularQ_dtor(struct CircularQ* _this)
{
    free(_this->mpData);
    _this->mpData = NULL;
}

struct CircularQ* CircularQ_operator_new(int cap)
{
    struct CircularQ* ret = (struct CircularQ*)malloc(sizeof(struct CircularQ));
    CircularQ_ctor(ret, cap);
    return ret;
}

void CircularQ_operator_delete (struct CircularQ* _this)
{
    CircularQ_dtor(_this);
    free(_this);
}