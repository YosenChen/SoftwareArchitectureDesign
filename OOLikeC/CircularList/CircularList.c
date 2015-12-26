#include "CircularList.h"

//operation APIs
BOOL CircularList_pop(struct CircularList* _this, int* ele)
{
    printf("CircularList_pop: isEmpty = %d, mpData[mEnd-1] = %d, mEnd = %d, mStart = %d\n"
        , _this->_base.isEmpty(&_this->_base)
        , _this->_base.mpData[(_this->_base.mEnd-1) >= 0 ? (_this->_base.mEnd - 1) : (_this->_base.mEnd - 1 + _this->_base.mCap)]
        , _this->_base.mEnd
        , _this->_base.mStart);

    if (_this->_base.isEmpty(&_this->_base)) return false;
    _this->_base.mEnd = (_this->_base.mEnd-1) >= 0 ? (_this->_base.mEnd - 1) : (_this->_base.mEnd - 1 + _this->_base.mCap);
    *ele = _this->_base.mpData[_this->_base.mEnd];
    if (_this->_base.mEnd == _this->_base.mStart) _this->_base.mIsEmpty = true;
    return true;
}
BOOL CircularList_push(struct CircularList* _this, int ele)
{
    printf("CircularList_push: isFull = %d, ele = %d, mEnd = %d, mStart = %d\n"
        , _this->_base.isFull(&_this->_base)
        , ele
        , _this->_base.mEnd
        , _this->_base.mStart);

    if (_this->_base.isFull(&_this->_base)) return false;
    _this->_base.mpData[_this->_base.mEnd] = ele;
    _this->_base.mEnd = (_this->_base.mEnd+1)%(_this->_base.mCap);
    _this->_base.mIsEmpty = false;
    return true;
}

//create, destroy APIs
void CircularList_ctor(struct CircularList* _this, int cap)
{
    CircularQ_ctor((struct CircularQ*)_this, cap);

    _this->pop = CircularList_pop;
    _this->push = CircularList_push;
}
void CircularList_dtor(struct CircularList* _this)
{
    CircularQ_dtor((struct CircularQ*)_this);
}
struct CircularList* CircularList_operator_new(int cap)
{
    struct CircularList* ret = (struct CircularList*)malloc(sizeof(struct CircularList));
    CircularList_ctor(ret, cap);
    return ret;
}
void CircularList_operator_delete (struct CircularList* _this)
{
    CircularList_dtor(_this);
    free(_this);
}