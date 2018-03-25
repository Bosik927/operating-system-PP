#pragma once
#include <array>
#include <queue>
#include <iostream>
#include <string>
#include "Process.h"

class Scheduler {
protected:
	//Proces ktory aktualnie posiada procesor 
	Process runningProcess;
	//Znacznik mowiacy o potrzebie wywlaszczenia procesora 
	bool needResched;

	//Wektor kolejek procesow aktywnych	
	std::array <std::queue<Process>, 16> activeProcesses;
	//Wektor kolejek procesow przeterminowanych 
	std::array <std::queue<Process>, 16> terminatedProcesses;

	//Wektor bitowy procesow aktywnych (jedynka oznacz ze dany priorytet posiada reprezentanta)
	std::array <bool, 16> bitsMapActive;
	//Wektor bitowy procesow przeterminowanch (jedynka oznacz ze dany priorytet posiada reprezentanta)
	std::array <bool, 16> bitsMapTerminated;
	//Procesy o statusie waiting - uspione
	std::vector <Process> waitingProcesses;

public:
	Scheduler();
	void addFirstProcess(PCB *process);
	void addProcess(PCB *process, unsigned int allNeedTime);
	unsigned int assignProcessor();
	void deleteProcess(unsigned int ID);
	void unsleep();
	void sleep(Process &process);
	void calculatePriority(Process &process, unsigned int allNeedTime);
	void translatePriority(Process &process);
	void giveTime(Process &process);
	void chooseProcess();
	void terminated();
	bool isTerminatedEmpty();
	void endOfEpoch();
	void reschedProcess();
	bool isActiveEmpty();
	void deleteWaitingProcess(unsigned int ID);
	void deleteActiveProcess(unsigned int ID);
	void deleteTerminatedProcess(unsigned int ID);

};