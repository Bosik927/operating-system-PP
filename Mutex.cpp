#include "Mutex.h"
#include <string>

Mutex::Mutex() : using_process(), waiting_processes(), is_lock(false) {}

Mutex::~Mutex() {}

void Mutex::lock(PCB &process) {
	if(using_process != nullptr && is_lock == true) {
		process.sleep();
		waiting_processes.push_back(&process);
	}
	else {
		using_process = &process;
		is_lock = true;
	}
}

bool Mutex::try_lock(PCB &process) {
	if(using_process == &process) return true;
	if(using_process == nullptr && is_lock == false) {
		using_process = &process;
		is_lock = true;
		return true;
	}
	return false;
}

void Mutex::unlock(PCB &process) {
	if(using_process == &process && is_lock == true) {
		using_process = nullptr;
		is_lock = false;
		if(waiting_processes.size() != 0) {
			using_process = waiting_processes[0];
			waiting_processes.erase(waiting_processes.begin());
			is_lock = true;
			using_process->wakeup();
		}
	}
}

PCB* Mutex::getUsingProcess() {
	return using_process;
}

std::vector<PCB *>* Mutex::getWaitingProcesses() {
	return &waiting_processes;
}

bool Mutex::isBlock() {
	return !is_lock;
}

std::string Mutex::toString() {
	std::string buffor = "Zamek";
	if (is_lock) {
		buffor += " zamkniety przez proces " + using_process->name + ";";
		if (waiting_processes.size() > 0) {
			buffor += " ilosc oczekujacych procesow: " + std::to_string(waiting_processes.size()) + ";";
		}
	}
	else {
		buffor += "otwarty";
	}
	return buffor;
}
