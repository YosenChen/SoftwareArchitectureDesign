#ifndef ITOP_H
#define ITOP_H

#include "ITopBase.h"

class ITop : public ITopBase
{
public:
	static ITop* create(ScenarioType scenType);
	void destroy(); //NOT allow derived class to redefine in virtual usage
	bool command(Cmd cmd); //NOT allow derived class to redefine in virtual usage
	void init(); //Not allow derived class to redefine in virtual usage
	void uninit(); //Not allow derived class to redefine in virtual usage
	static void mainProcessLoop(void* arg);
	
	ITop(ScenarioType scenType)
		:mScenType(scenType)
	{
		cout << __FUNCTION__ << "()\n";
		cout << "mScenType = " << (int)mScenType << "\n";
	}
protected:
	int mScenType;
};

template <ScenarioType scenType>
class ITopCase : public ITop
{
public:
	static ITopCase* getInstance()
	{
		cout << __FUNCTION__ << "() return ITopCase<" << (int)scenType << ">\n";
		static ITopCase<scenType> singleton;
		printf("ITopCase<scenType> singleton addr = %p\n", &singleton);

		return &singleton;
	}
	ITopCase()
		:ITop(scenType)
	{
		cout << __FUNCTION__ << "()\n";
		cout << "mScenType = " << (int)mScenType << "\n";
	}
};

#endif
