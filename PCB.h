#pragma once
#include <string>
#include <iostream>

class PCB {
public:

	PCB(std::string name, int prio) {
		this->name = name;
		this->basePriority = prio;
	}
	PCB() {}

	enum processState { newbie, waiting, ready, active, finished };
	std::string name;
	int ID;
	processState state;
	bool blocked;
	int priority;
	int basePriority;
	int commandCounter;
	int A;
	int B;
	int C;
	int D;
	void print();
	void sleep();
	void wakeup();
};