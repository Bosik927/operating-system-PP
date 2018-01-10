#pragma once
#include "PCB.h"

// Klasa Process skladajaca sie z pola PCB (proces), restTime (pozostaly kwant czasu), waitingTime (czas ktory oczekuje na kwant czasu)
// allNeedTime (czas potrzebny do pelnego wykonania programu)
class Process
{
protected:
	unsigned int restTime;
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