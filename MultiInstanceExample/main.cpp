
#include "ITopBase.h"


int main(void)
{
    ITopBase* pITopBase = ITopBase::create(Scenario_1);
    Property_T prop;
    pITopBase->getProp(prop);
    pITopBase->command(Cmd_State1_Start);

    ITopBase* pITopBase_2 = ITopBase::create(Scenario_2);
    pITopBase_2->command(Cmd_State3_Start);
    


    getchar();
    return 0;
}
