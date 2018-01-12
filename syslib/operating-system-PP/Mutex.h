#pragma once
#include "ProcessManagement.h"
#include <vector>

class Mutex {
private:
	std::vector<PCB*> waiting_processes;
	PCB* using_process;
	bool is_lock;
public:
	Mutex();
	~Mutex();

	bool lock(PCB& process);
	bool try_lock(PCB& process);
	void unlock(PCB& process);

	std::vector<PCB*>* getWaitingProcesses();
	PCB* getUsingProcess();
	bool isBlock();

	std::string toString();
};