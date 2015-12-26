#ifndef _IMPLEMENTATION_CLASS_H_
#define _IMPLEMENTATION_CLASS_H_

#include "Interface.h"

struct ImpA
{
//inherit from Interface
    struct Interface _base;

//implementation functions, variables
	int a;
	BOOL (*show_a) (struct ImpA* _this);
};

BOOL ImpA_enter (struct Interface* _this, int id);
BOOL ImpA_execute (struct Interface* _this, char* str);
BOOL ImpA_exit (struct Interface* _this);

BOOL ImpA_show_a (struct ImpA* _this); 

void ImpA_ctor (struct ImpA* _this);
void ImpA_dtor (struct ImpA* _this);

struct ImpB
{
//inherit from Interface
    struct Interface _base;

//implementation functions, variables
	int b;
	BOOL (*show_b) (struct ImpB* _this);
};

BOOL ImpB_enter (struct Interface* _this, int id);
BOOL ImpB_execute (struct Interface* _this, char* str);
BOOL ImpB_exit (struct Interface* _this);

BOOL ImpB_show_b (struct ImpB* _this); 

void ImpB_ctor (struct ImpB* _this);
void ImpB_dtor (struct ImpB* _this);

#endif