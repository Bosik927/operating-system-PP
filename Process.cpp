#include "Process.h"

Process::Process() {}
Process::Process(PCB* process)
{
	this->process = process;
	restTime = 0;
	waitingTime = 0;
	allNeedTime = 0; //NADAC MU ODPOWIEDNI CZAS OD ARTURA
}

void Process::incWaitingTime() {
	waitingTime++;
}
void Process::decRestTime() {
	this->restTime--;
}

void Process::setRestTime(unsigned int time)
{
	restTime = time;
}
void Process::setWaitingTime(unsigned int time)
{
	waitingTime = time;
}
void Process::setAllNeedTime(unsigned int time) {
	allNeedTime = time;
}

unsigned int Process::getRestTime()
{
	return restTime;
}
unsigned int Process::getWaitingTime()
{
	return waitingTime;
}
unsigned int Process::getAllNeedTime()
{
	return allNeedTime;
}