#include "Interface.h"
#include "ImplementationClass.h"

#include <stdio.h>
#include <stdlib.h>

static struct ImpA sImpA;
static struct ImpB sImpB;

struct Interface* initStaticInterface(enum EImpType type)
{
    printf("initStaticInterface: type = %d, ", type);

    if (type == EImpType_A)
    {
        ImpA_ctor(&sImpA);
        printf("&sImpA = %p\n", &sImpA);
        return (struct Interface*)&sImpA;
    }
    else if (type == EImpType_B)
    {
        ImpB_ctor(&sImpB);
        printf("&sImpB = %p\n", &sImpB);
        return (struct Interface*)&sImpB;
    }
    else 
        printf("type error: type = %d\n", type);
    return 0;
}
void uninitStaticInterface(struct Interface** _this, enum EImpType type)
{
    printf("uninitStaticInterface: type = %d, *_this = %p\n", type, *_this);

    if ((type == EImpType_A) && ((void*)*_this == (void*)&sImpA))
    {
        ImpA_dtor(&sImpA);
        *_this = 0;
    }
    else if ((type == EImpType_B) && ((void*)*_this == (void*)&sImpB))
    {
        ImpB_dtor(&sImpB);
        *_this = 0;
    }
    else 
        printf("type error: type = %d, *_this = %p\n", type, *_this);
}

struct Interface* createInterface(enum EImpType type)
{
    struct Interface* ret = 0;

    printf("createInterface: type = %d, ", type);
    if (type == EImpType_A)
    {
        ret = (struct Interface*)calloc(1, sizeof(struct ImpA));
        ImpA_ctor((struct ImpA*)ret);
        printf("return ImpA addr: %p\n", ret);
        return ret;
    }
    else if (type == EImpType_B)
    {
        ret = (struct Interface*)calloc(1, sizeof(struct ImpB));
        ImpB_ctor((struct ImpB*)ret);
        printf("return ImpB addr: %p\n", ret);
        return ret;
    }
    else
        printf("type error: type = %d\n", type);

    return 0;

}

void destroyInterface(struct Interface** _this, enum EImpType type)
{
    printf("destroyInterface: type = %d, *_this = %p, (*_this)->mType = %d\n", type, *_this, (*_this)->mType);
    if (((*_this)->mType == EImpType_A) && (type == EImpType_A))
    {
        ImpA_dtor((struct ImpA*)*_this);
        free(*_this);
        *_this = 0;
    }
    else if (((*_this)->mType == EImpType_B) && (type == EImpType_B))
    {
        ImpB_dtor((struct ImpB*)*_this);
        free(*_this);
        *_this = 0;
    }
    else
        printf("type error: type = %d, (*_this)->mType = %d\n", type, (*_this)->mType);

}
