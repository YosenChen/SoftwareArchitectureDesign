#include "ImplementationClass.h"
#include <stdio.h>


//base APIs
BOOL ImpA_enter (struct Interface* _this, int id)
{
    struct ImpA* _this_ImpA = (struct ImpA*)_this;
    printf("ImpA_enter: type=%d\n", _this->mType);
    if (_this->mType != EImpType_A) {printf("Type error!\n"); return false;}
    
    _this_ImpA->show_a(_this_ImpA);
    printf("ImpA_enter id = %d\n", id);
    return true;
}

BOOL ImpA_execute (struct Interface* _this, char* str)
{
    struct ImpA* _this_ImpA = (struct ImpA*)_this;
    printf("ImpA_execute: type=%d\n", _this->mType);
    if (_this->mType != EImpType_A) {printf("Type error!\n"); return false;}

    _this_ImpA->show_a(_this_ImpA);
    printf("ImpA_execute str = %s\n", str);
    return true;
}
BOOL ImpA_exit (struct Interface* _this)
{
    struct ImpA* _this_ImpA = (struct ImpA*)_this;
    printf("ImpA_exit: type=%d\n", _this->mType);
    if (_this->mType != EImpType_A) {printf("Type error!\n"); return false;}

    _this_ImpA->show_a(_this_ImpA);
    return true;
}


void ImpA_ctor (struct ImpA* _this)
{
    printf("ImpA_ctor\n");
    _this->_base.mType = EImpType_A;
    _this->_base.enter = ImpA_enter;
    _this->_base.execute = ImpA_execute;
    _this->_base.exit = ImpA_exit;
    _this->a = 100;
    _this->show_a = ImpA_show_a;
}
void ImpA_dtor (struct ImpA* _this)
{
    printf("ImpA_dtor\n");
}
BOOL ImpA_show_a (struct ImpA* _this)
{
    printf("ImpA_show_a, a = %d\n", _this->a);
    return true;
}

//base APIs
BOOL ImpB_enter (struct Interface* _this, int id)
{
    struct ImpB* _this_ImpB = (struct ImpB*)_this;
    printf("ImpB_enter: type=%d\n", _this->mType);
    if (_this->mType != EImpType_B) {printf("Type error!\n"); return false;}

    _this_ImpB->show_b(_this_ImpB);
    printf("ImpB_enter id = %d\n", id);
    return true;
}
BOOL ImpB_execute (struct Interface* _this, char* str)
{
    struct ImpB* _this_ImpB = (struct ImpB*)_this;
    printf("ImpB_execute: type=%d\n", _this->mType);
    if (_this->mType != EImpType_B) {printf("Type error!\n"); return false;}

    _this_ImpB->show_b(_this_ImpB);
    printf("ImpB_execute str = %s\n", str);
    return true;
}
BOOL ImpB_exit (struct Interface* _this)
{
    struct ImpB* _this_ImpB = (struct ImpB*)_this;
    printf("ImpB_exit: type=%d\n", _this->mType);
    if (_this->mType != EImpType_B) {printf("Type error!\n"); return false;}

    _this_ImpB->show_b(_this_ImpB);
    return true;
}

void ImpB_ctor (struct ImpB* _this)
{
    printf("ImpB_ctor\n");
    _this->_base.mType = EImpType_B;
    _this->_base.enter = ImpB_enter;
    _this->_base.execute = ImpB_execute;
    _this->_base.exit = ImpB_exit;
    _this->b = 200;
    _this->show_b = ImpB_show_b;
}
void ImpB_dtor (struct ImpB* _this)
{
    printf("ImpB_dtor\n");
}

BOOL ImpB_show_b (struct ImpB* _this)
{
    printf("ImpB_show_b, b = %d\n", _this->b);
    return true;
}
