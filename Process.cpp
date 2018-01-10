#include "Process.h"

Process::Process() {}
//NADAC MU ODPOWIEDNI CZAS OD ARTURA
Process::Process(PCB* process)
{
	this->process = process;
	restTime = 0;
	allNeedTime = 0; 
}


void Process::decRestTime() {
	this->restTime--;
}

void Process::setRestTime(unsigned int time)
{
	restTime = time;
}
void Process::setAllNeedTime(unsigned int time) {
	allNeedTime = time;
}

unsigned int Process::getRestTime()
{
	return restTime;
}
unsigned int Process::getAllNeedTime()
{
	return allNeedTime;
}