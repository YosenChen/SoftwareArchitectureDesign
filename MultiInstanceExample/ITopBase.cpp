
#include "ITopBase.h"
#include "ITop.h"

using namespace std;

ITopBase* ITopBase::create(ScenarioType scenType)
{
    cout << __FUNCTION__ << "()\n";
    if (scenType == 0)
    {
        cout << "return ITopBase\n";
        static ITopBase singleton;
        return &singleton;
    }
    else
    {
        cout << "return ITop::create(scenType)\n";
        return ITop::create(scenType);
    }
}
