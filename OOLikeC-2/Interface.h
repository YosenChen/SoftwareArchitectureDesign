#ifndef _INTERFACE_H_
#define _INTERFACE_H_

typedef char      BOOL;
#define true      1
#define false     0

enum EImpType
{
    EImpType_NONE = 0, //to avoid uninit case
    EImpType_A,
    EImpType_B,
    NUM_IMP_TYPE
};


struct Interface
{
    enum EImpType mType;
    BOOL (*enter) (struct Interface* _this, int id);
    BOOL (*execute) (struct Interface* _this, char* str);
    BOOL (*exit) (struct Interface* _this);
};

//static Interface
struct Interface* initStaticInterface(enum EImpType type);
void uninitStaticInterface(struct Interface** _this, enum EImpType type);

//create on demand
struct Interface* createInterface(enum EImpType type);
void destroyInterface(struct Interface** _this, enum EImpType type);


#endif
