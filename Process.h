#pragma once
#include "PCB.h"

class Process
{
protected:
	//Pozostaly kwant czasu
	unsigned int restTime;
	//Pozostaly kwant czasu, do zakonczenia procesu
	unsigned int allNeedTime;

public:
	PCB * process;
	Process();
	Process(PCB* process);
	void decRestTime();
	void setRestTime(unsigned int time);
	void setAllNeedTime(unsigned int time);
	unsigned int getRestTime();
	unsigned int getAllNeedTime();
};