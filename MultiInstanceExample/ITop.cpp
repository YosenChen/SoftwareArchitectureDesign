
#include "ITop.h"

using namespace std;

ITop* ITop::create(ScenarioType scenType)
{
	cout << __FUNCTION__ << "(" << (int)scenType << ")\n";
	if (scenType & Scenario_1)
	{
		ITopCase<Scenario_1>::getInstance()->init();
		return ITopCase<Scenario_1>::getInstance();
	}
	if (scenType & Scenario_2)
	{
		ITopCase<Scenario_2>::getInstance()->init();
		return ITopCase<Scenario_2>::getInstance();
	}
	if (scenType & Scenario_12)
	{
		ITopCase<Scenario_12>::getInstance()->init();
		return ITopCase<Scenario_12>::getInstance();
	}
	//else
	{
		ITopCase<Scenario_Default>::getInstance()->init();
		return ITopCase<Scenario_Default>::getInstance();
	}
}

void ITop::destroy()
{
	cout << __FUNCTION__ << "()\n";
	uninit();
}

void ITop::init()
{
	cout << __FUNCTION__ << "()\n";
	

}

void ITop::uninit()
{
	cout << __FUNCTION__ << "()\n";

}

bool ITop::command(Cmd cmd)
{
	cout << __FUNCTION__ << "(" << (int)cmd << ")\n";
	cout << "mScenType = " << (int)mScenType << "\n";
	return true;
}
