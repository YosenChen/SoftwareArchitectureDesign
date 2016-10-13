#ifndef ITopBASE_H
#define ITopBASE_H

#include <iostream>
#include <cstdio>

using namespace std;

enum ScenarioType
{
    Scenario_Default    = 0x0,
    Scenario_1            = 0x1,
    Scenario_2            = 0x2,
    Scenario_12            = 0x4
};


enum Cmd
{
    Cmd_Init                = 0,
    Cmd_Uninit,
    Cmd_State1_Start,
    Cmd_State1_End,
    Cmd_State2_Start,
    Cmd_State2_End,
    Cmd_State3_Start,
    Cmd_State3_End,

    Cmd_Number
};

struct Property_T
{
    bool enableModule1;
    bool enableModule2;
    int param1;
    int param2;
    Property_T()
        :enableModule1(false)
        ,enableModule2(false)
        ,param1(30)
        ,param2(5)
    {}
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++
//Top interface and trivial implementation
//+++++++++++++++++++++++++++++++++++++++++++++++++++++
class ITopBase
{
public:
    static ITopBase* create(ScenarioType scenType);
    virtual void destroy() {};
    virtual bool command(Cmd cmd)  //allow derived class to redefine in virtual usage
    {
        cout << __FUNCTION__ << "(" << (int)cmd << ")\n";
        return true;
    }
    virtual void setProp(Property_T prop) {cout << __FUNCTION__ << "()\n";} //allow derived class to redefine in virtual usage
    virtual void getProp(Property_T& prop) {cout << __FUNCTION__ << "()\n";} //allow derived class to redefine in virtual usage
};

#endif
