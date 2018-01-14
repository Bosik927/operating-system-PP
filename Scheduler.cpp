#include <array>
#include <queue>
#include <iostream>
#include <string>
#include "Scheduler.h"

//Konstruktor wyzerowanie map bitowych i znaczniki needResched i lastTerminated
Scheduler::Scheduler() {
	bitsMapActive.fill(0);
	bitsMapTerminated.fill(0);
	needResched = 0;
	lastTerminated = 0;
}

//Dodawanie procesu bezczynnosci
void Scheduler::addFirstProcess(PCB *process) {

	Process newProcess = Process(process);
	newProcess.process->priority = 15;

	giveTime(newProcess);
	runningProcess = newProcess;
}

//Dodawanie procesu do kolejki procesow, odpowiednie ustawienie mapy bitowej i nadanie kwantu czasu 
//Jesli nowy proces ma priorytet wyzszy to zostaje ustawiony znacznik needResched
void Scheduler::addProcess(PCB *process, unsigned int allNeedTime)
{
	Process newProcess = Process(process);
	calculateFirstTimeCurrentPriority(newProcess, allNeedTime);

	if (newProcess.process->priority < runningProcess.process->priority)
	{
		needResched = 1;
	}
	giveTime(newProcess);

	if (bitsMapActive[newProcess.process->priority] == 0) { bitsMapActive[process->priority] = 1; }
	activeProcesses[newProcess.process->priority].push(newProcess);
}

//Obliczanie priorytetu pierwszy raz
void Scheduler::calculateFirstTimeCurrentPriority(Process &process, unsigned int allNeedTime)
{
	process.setAllNeedTime(allNeedTime);
	translatePriority(process);

}

//Mapowanie z windowsowych priorytetow na Linuxowe
void Scheduler::translatePriority(Process &process)
{
	switch (process.process->basePriority)
	{
	case 0:
		process.process->priority = 15;
		break;
	case 1:
		process.process->priority = 14;
		break;
	case 2:
		process.process->priority = 13;
		break;
	case 3:
		process.process->priority = 12;
		break;
	case 4:
		process.process->priority = 11;
		break;
	case 5:
		process.process->priority = 10;
		break;
	case 6:
		process.process->priority = 9;
		break;
	case 7:
		process.process->priority = 8;
		break;
	case 8:
		process.process->priority = 7;
		break;
	case 9:
		process.process->priority = 6;
		break;
	case 10:
		process.process->priority = 5;
		break;
	case 11:
		process.process->priority = 4;
		break;
	case 12:
		process.process->priority = 3;
		break;
	case 13:
		process.process->priority = 2;
		break;
	case 14:
		process.process->priority = 1;
		break;
	case 15:
		process.process->priority = 0;
		break;
	}
}

//Nadawanie kwantu czasu
void Scheduler::giveTime(Process &process)
{
	if (process.process->priority < 8) {
		process.setRestTime(process.getAllNeedTime());
	}
	else {
		switch (process.process->priority)
		{
		case 8: {
			process.setRestTime(8);
			break;
		}
		case 9: {
			process.setRestTime(7);
			break;
		}
		case 10: {
			process.setRestTime(6);
			break;
		}
		case 11: {
			process.setRestTime(5);
			break;
		}
		case 12: {
			process.setRestTime(4);
			break;
		}
		case 13: {
			process.setRestTime(3);
			break;
		}
		case 14: {
			process.setRestTime(2);
			break;
		}
		case 15: {
			process.setRestTime(1);
			break;
		}
		}

	}
}

//wybieranie procesu do dzialania, wyciaganie go z kolejki i zwracanie
//odpowiednie ustawienie mapy bitowej
void Scheduler::chooseProcess()
{
	unsigned int numChoice;
	for (int i = 0; i < 16; i++)
	{
		if (bitsMapActive[i] == 1)
		{
			numChoice = i;
			break;
		}
	}

	Process choice = activeProcesses[numChoice].front();
	activeProcesses[numChoice].pop();

	//Jezeli wyjety proces to jedyny proces o tym priorytecie 
	if (activeProcesses[numChoice].empty()) { bitsMapActive[numChoice] = 0; }

	runningProcess = choice;
}

//wydziedziczenie procesora
void Scheduler::reschedProcess()
{
	if (bitsMapActive[runningProcess.process->priority] == 0) { bitsMapActive[runningProcess.process->priority] = 1; }
	activeProcesses[runningProcess.process->priority].push(runningProcess);
	chooseProcess();
	needResched = 0;
}

//Zwraca proces ktory otrzymal procesor 
unsigned int Scheduler::assignProcessor()
{
	unsleep();

	//gdy running to idle + pusta active + pusta terminated
	if (!isTerminatedEmpty() && !isActiveEmpty()) {
		return runningProcess.process->ID;
	}
	else {
		// gdy running to idle + pusta active  + nie pusta terminated
		// koncze epoke i wydziedziczam proces idle
		if (!isActiveEmpty())
		{
			endOfEpoch();
			reschedProcess();

			runningProcess.decRestTime();
			if (runningProcess.getRestTime() == 0) {
				auto actualRunningID = runningProcess.process->ID;
				terminated();
				chooseProcess();
				return actualRunningID;
			}

			return runningProcess.process->ID;
		}
		else // gdy active nie jest pusta
		{
			if (needResched == 1) {
				reschedProcess();
			}

			//gdy trafia na process o statusie waiting
			while (runningProcess.process->state == PCB::processState::waiting)
			{
				sleep(runningProcess);
				chooseProcess();
			}
			//gdy wszystkie waiting minal i jest pusta active
			if (!isActiveEmpty())
			{
				endOfEpoch();
				reschedProcess();

				runningProcess.decRestTime();
				if (runningProcess.getRestTime() == 0) {
					auto actualRunningID = runningProcess.process->ID;
					terminated();
					chooseProcess();
					return actualRunningID;
				}

				return runningProcess.process->ID;
			}

			// gdy trafiony proces nie jest waiting
			runningProcess.decRestTime();

			if (runningProcess.getRestTime() == 0) {
				auto actualRunningID = runningProcess.process->ID;
				terminated();
				chooseProcess();
				return actualRunningID;
			}

			return runningProcess.process->ID;
		}
	}

}


//Dodawanie do procesow aktywnych z tablicy waitingProcesses, odpowiednie uzupelnienie bitsMapActive, usuwanie procesu z tablicy waiting
//Funkcja wykorzystuje wlasnosc iz numer ID jest unikalny i po trafieniu konczy dzialanie petli
void Scheduler::unsleep()
{
	for (int i = 0; i < waitingProcesses.size(); i++)
	{
		if (waitingProcesses[i].process->state == PCB::processState::ready)
		{
			activeProcesses[waitingProcesses[i].process->priority].push(waitingProcesses[i]);
			bitsMapActive[waitingProcesses[i].process->priority] = 1;

			if (waitingProcesses[i].process->priority < runningProcess.process->priority) {
				needResched = 1;
			}

			waitingProcesses.erase(waitingProcesses.begin() + i);
		}
	}

}

//Dodawanie do procesow waiting
void Scheduler::sleep(Process &process)
{
	waitingProcesses.push_back(process);
}

//Wrzucenie procesow aktywnych ktore wykorzystaly swoj kwant czasu do procesow przeterminowanych
//Przeliczenie ponowne priorytetu, nadanie mu odpowiedniego kwantu czasu
void Scheduler::terminated()
{
	giveTime(runningProcess);

	if (bitsMapTerminated[runningProcess.process->priority] == 0)
	{
		bitsMapTerminated[runningProcess.process->priority] = 1;
	}
	terminatedProcesses[runningProcess.process->priority].push(runningProcess);
}

//Funkcja sprawdzajaca czy w tablicy procesow przeterminowanych jest pusto
bool Scheduler::isTerminatedEmpty() {
	for (auto e : bitsMapTerminated)
	{
		if (e == 1)
		{
			return 1;
		}
	}
	return 0;
}

//Funkcja sprawdzajaca czy w tablicy procesow actywnej jest pusto
bool Scheduler::isActiveEmpty() {
	for (auto e : bitsMapActive)
	{
		if (e == 1)
		{
			return 1;
		}
	}
	return 0;
}

//Przeniesienie wszystkich procesow z przeterminowanych do aktywnych 
//Wyczyszczenie bitowej mapy procesow przetermiowanych
void Scheduler::endOfEpoch()
{
	for (int i = 0; i < 16; i++)
	{
		while (!terminatedProcesses[i].empty())
		{
			auto process = terminatedProcesses[i].front();
			terminatedProcesses[i].pop();

			if (bitsMapActive[i] == 0) { bitsMapActive[i] = 1; }
			activeProcesses[i].push(process);
		}
	}

	//Czyszczenie mapy bitowej
	for (auto &e : bitsMapTerminated)
	{
		e = 0;
	}
}

//Usuniecie procesu z kolejki procesow (przez zarzadzanie procesami)
void Scheduler::deleteProcess(unsigned int ID)
{
	if (runningProcess.process->ID == ID) {
		chooseProcess();
	}
	else {
		deleteActiveProcess(ID);
		deleteTerminatedProcess(ID);
		deleteWaitingProcess(ID);
	}
}

//Przeszukiwanie i usuniecie z tablicy procesow aktywnych procesu o podanym ID
void Scheduler::deleteActiveProcess(unsigned int ID) {
	for (int i = 0; i < activeProcesses.size(); i++)
	{
		if (!activeProcesses[i].empty())
		{
			if (activeProcesses[i].front().process->ID == ID)
			{
				auto beginQueue = activeProcesses[i].front();
				activeProcesses[i].pop();
				if (activeProcesses[i].empty()) {
					bitsMapActive[i] = 0;
				}
				break;

			}
			else {
				auto beginQueue = activeProcesses[i].front();
				activeProcesses[i].pop();
				activeProcesses[i].push(beginQueue);
				while (beginQueue.process->ID != activeProcesses[i].front().process->ID)
				{
					if (ID == activeProcesses[i].front().process->ID) {
						activeProcesses[i].pop();
						break;
					}
					else
					{
						auto  element = activeProcesses[i].front();
						activeProcesses[i].pop();
						activeProcesses[i].push(element);
					}
				}
			}
		}
	}
}

//Przeszukiwanie i usuniecie z tablicy procesow przetermiowanych procesu o podanym ID
void Scheduler::deleteTerminatedProcess(unsigned int ID) {
	for (int i = 0; i < terminatedProcesses.size(); i++)
	{
		if (!terminatedProcesses[i].empty())
		{
			if (terminatedProcesses[i].front().process->ID == ID)
			{
				auto beginQueue = terminatedProcesses[i].front();
				terminatedProcesses[i].pop();
				if (terminatedProcesses[i].empty()) {
					bitsMapTerminated[i] = 0;
				}
				break;
			}
			else {
				auto beginQueue = terminatedProcesses[i].front();
				terminatedProcesses[i].pop();
				terminatedProcesses[i].push(beginQueue);
				while (beginQueue.process->ID != terminatedProcesses[i].front().process->ID)
				{
					if (ID == terminatedProcesses[i].front().process->ID) {
						terminatedProcesses[i].pop();
						break;
					}
					else
					{
						auto  element = terminatedProcesses[i].front();
						terminatedProcesses[i].pop();
						terminatedProcesses[i].push(element);
					}
				}
			}
		}
	}
}

//Przeszukiwanie i usuniecie z tablicy procesow waiting procesu o podanym ID
void Scheduler::deleteWaitingProcess(unsigned int ID)
{
	for (int i = 0; i < waitingProcesses.size(); i++)
	{
		if (ID == waitingProcesses[i].process->ID)
		{
			waitingProcesses.erase(waitingProcesses.begin() + i);
			break;
		}
	}

}


//METODY PRZEZNACZONE DO SHELLA
void Scheduler::displayActiveProcesses()
{
	std::cout << "ACTIVE:" << std::endl;
	auto copyActiveProcesses = activeProcesses;

	for (auto e : copyActiveProcesses)
	{
		if (!e.empty()) std::cout << "Procesy o priorytecie " << e.front().process->priority << ":" << std::endl;
		while (!e.empty())
		{
			auto process = e.front();
			e.pop();

			std::cout << process.process->display() << " kwant: " << process.getRestTime() << std::endl;
		}
	}
}
void Scheduler::displayTerminatedProcesses() {

	std::cout << "TERMINATED:" << std::endl;
	auto copyTerminatedProcesses = terminatedProcesses;

	for (auto e : copyTerminatedProcesses)
	{
		if (!e.empty()) std::cout << "Procesy o priorytecie " << e.front().process->priority << ":" << std::endl;
		while (!e.empty())
		{
			auto process = e.front();
			e.pop();

			std::cout << "NAME: " << process.process->name << " KWANT: " << process.getRestTime() << std::endl;
		}
	}
}
void Scheduler::displayActiveBitsMap() {
	std::cout << "ACTIVE BITS MAP:  ";
	for (int i = 1; i < bitsMapActive.size() + 1; i++)
	{
		if (i % 4 == 0) {
			std::cout << bitsMapActive[i - 1] << " ";
		}
		else {
			std::cout << bitsMapActive[i - 1];
		}
	}
	std::cout << std::endl;
}
void Scheduler::displayTerminatedBitsMap() {
	std::cout << "TERMINATED BITS MAP:";
	for (int i = 1; i < bitsMapTerminated.size() + 1; i++)
	{
		if (i % 4 == 0) {
			std::cout << bitsMapTerminated[i - 1] << " ";
		}
		else {
			std::cout << bitsMapTerminated[i - 1];
		}
	}
	std::cout << std::endl;
}
void Scheduler::displayRunningProcess() {
	std::cout << "PROCESOR: " << runningProcess.process->name << " KWANT: " << runningProcess.getRestTime() << " PRIORITY " << runningProcess.process->priority << std::endl;
}
void Scheduler::displayWaitingProcesses() {
	std::cout << "WAITING:" << std::endl;

	for (auto e : waitingProcesses)
	{
		std::cout << "NAME: " << e.process->name << " KWANT: " << e.getRestTime() << std::endl;
	}
}
void Scheduler::displayAll() {
	displayActiveProcesses();
	displayActiveBitsMap();
	displayTerminatedProcesses();
	displayTerminatedBitsMap();
	displayWaitingProcesses();
	displayRunningProcess();
	std::cout << "Resched: " << needResched << std::endl;
	std::cout << std::endl;
}
