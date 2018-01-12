#include "PCB.h"


void PCB::Sleep()
{
	this->state = processState::waiting;
}

void PCB::WakeUp()
{
	this->state = processState::ready;
}
//Zwraca opis stanu procesu w postaci stringa
std::string PCB::displayState()
{
	switch (this->state)
	{
	case processState::active:
		return "active";
	case processState::newbie:
		return "new";
	case processState::ready:
		return "ready";
	case processState::waiting:
		return "waiting";
	case processState::finished:
		return "finished";
	default:
		return "error";
	}
}

//Drukowanie zawartoœci pola PCB
std::string PCB::display()
{
	return "Proces: " + name + ", identyfikator: " + std::to_string(ID) + ", stan: " + displayState() + ", priorytet bazowy: " + std::to_string(basePriority) + ", aktualny priorytet: " + std::to_string(priority) + ", rejestry A: " + std::to_string(A) + ", B: " + std::to_string(B) + ", C: " + std::to_string(C) + ", D: " + std::to_string(D) + "\n";
}


