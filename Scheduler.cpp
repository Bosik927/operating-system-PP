#include <array>
#include <queue>
#include <iostream>
#include <string>
#include "Scheduler.h"

//Konstruktor wyzerowanie mapy bitowej
Scheduler::Scheduler() {
	bitsMapActive.fill(0);
	bitsMapTerminated.fill(0);
	needResched = 0;
}

//Dodawanie procesu bezczynnosci
void Scheduler::addFirstProcess(PCB *process) {

	Process newProcess = Process(process);
	newProcess.process->priority = 15;

	giveTime(newProcess);
	runningProcess = newProcess;
}

//Dodawanie procesu do kolejki procesow (przez zarzadzanie procesami), odpowiednie ustawienie mapy bitowej i nadanie kwantu czasu 
//Jesli nowy proces ma priorytet wyzszy to zostaje ustawiony znacznik needResched
void Scheduler::addProcess(PCB *process)
{
	Process newProcess = Process(process);
	calculateFirstTimeCurrentPriority(newProcess);

	if (newProcess.process->priority < runningProcess.process->priority)
	{
		needResched = 1;
	}
	giveTime(newProcess);

	if (bitsMapActive[newProcess.process->priority] == 0) { bitsMapActive[process->priority] = 1; }
	activeProcesses[newProcess.process->priority].push(newProcess);
}

//Dodawanie do procesow aktywnych
void Scheduler::unsleep(int ID)
{
	for (int i = 0; i < waitingProcesses.size(); i++)
	{
		if (waitingProcesses[i].process->ID == ID)
		{
			if (bitsMapActive[waitingProcesses[i].process->priority] == 0) { bitsMapActive[waitingProcesses[i].process->priority] = 1; }
			activeProcesses[waitingProcesses[i].process->priority].push(waitingProcesses[i]);

			waitingProcesses.erase(waitingProcesses.begin()+i);
		}
	}

}

//Dodawanie do procesow waiting
void Scheduler::sleep(int ID)
{
	for (auto &e : activeProcesses)
	{
		if (!e.empty()) {
			auto process = e.front();
			if (process.process->ID == ID)
			{
				waitingProcesses.push_back(process);
				e.pop();
			}
		}
	}

}

//Obliczanie priorytetu pierwszy raz
void Scheduler::calculateCurrentPriority(Process &process) {
	unsigned int rest = process.getRestTime(), waiting = process.getWaitingTime(), need = process.getAllNeedTime();

	if (process.getWaitingTime() > process.getAllNeedTime()) {
		if (process.process->priority > 8) {
			process.process->priority--;
		}
	}
}

//Obliczanie aktualnego priorytetu (kazdorazowo po zakonczeniu kwantu czasu, przez proces)
void Scheduler::calculateFirstTimeCurrentPriority(Process &process)
{
	unsigned int rest = process.getRestTime(), waiting = process.getWaitingTime(), need = process.getAllNeedTime();

	translate(process);

	if (process.getWaitingTime() > process.getAllNeedTime()) {

	}
}

//Mapowanie z windowsowych priorytetow na Linuxowe
void Scheduler::translate(Process &process)
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

//UZUPELNIC DLUGOSC PROGRAMU robi sie
//Nadawanie kwantu czasu
void Scheduler::giveTime(Process &process)
{
	switch (process.process->priority)
	{
	case 0: {
		process.setRestTime(16);
		break;
	}
	case 1: {
		process.setRestTime(15);
		break;
	}
	case 2: {
		process.setRestTime(14);
		break;
	}
	case 3: {
		process.setRestTime(13);
		break;
	}
	case 4: {
		process.setRestTime(12);
		break;
	}
	case 5: {
		process.setRestTime(11);
		break;
	}
	case 6: {
		process.setRestTime(10);
		break;
	}
	case 7: {
		process.setRestTime(9);
		break;
	}
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
	default:
		//UZUPELNIC O DLUGOSC PROGRAMU
		process.setRestTime(1);
		break;
	}

}

//FUNKCJA USUWANIA PROCESU OD ADAMA
//Usuniecie procesu z kolejki procesow (przez zarzadzanie procesami)
void Scheduler::deleteProcess(Process &process)
{
	//USUN ADAM TEN PROCES
	//JA GO NIE MAM W KOLEJCE WIEC "ZAPOMINAM" O NIM
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

//Przydzial procesora do odpowiedniego procesu (procesor)
void Scheduler::assignProcessor() // arg Interpreter &inter
{

	if (runningProcess.process->name == "idle" && !isTerminatedEmpty() && !isActiveEmpty())
	{
		/// bool run(runningProcess.process); //proces bezczynnosci
	}
	else {
		//Sprawdza czy nie trzeba zmienic procesu
		if (needResched == 1)
		{
			reschedProcess();
		}

		//Sprawdza czy nie czas na zmiane epoki
		if (runningProcess.process->name == "idle" && isTerminatedEmpty())
		{
			endOfEpoch();
			reschedProcess();
		}

		/// bool run(runningProcess.process);

		runningProcess.decRestTime();

		if (runningProcess.getRestTime() == 0)
		{
			terminated(runningProcess);
			chooseProcess();
		}

		incWaitingTime();
	}
}

//wydzielenie procesora
void Scheduler::reschedProcess()
{
	if (bitsMapActive[runningProcess.process->priority] == 0) { bitsMapActive[runningProcess.process->priority] = 1; }
	activeProcesses[runningProcess.process->priority].push(runningProcess);
	runningProcess.setWaitingTime(0);
	chooseProcess();
}

//Inkrementowanie pola waitingTime dla odpowiednich procesow
void Scheduler::incWaitingTime() {

	auto copyQueue = activeProcesses;
	for (auto e : copyQueue)
	{
		while (!e.empty())
		{
			auto process = e.front();
			e.pop();

			process.incWaitingTime();
		}
	}

	copyQueue = terminatedProcesses;
	for (auto e : copyQueue)
	{
		while (!e.empty())
		{
			auto process = e.front();
			e.pop();

			process.incWaitingTime();
		}
	}
}


//Wrzucenie procesow aktywnych ktore wykorzystaly swoj kwant czasu do procesow przeterminowanych
//Przeliczenie ponowne priorytetu, nadanie mu odpowiedniego kwantu czasu
void Scheduler::terminated(Process &process)
{
	calculateCurrentPriority(process);
	giveTime(process);
	process.setWaitingTime(0);

	if (bitsMapTerminated[process.process->priority] == 0)
	{
		bitsMapTerminated[process.process->priority] = 1;
	}
	terminatedProcesses[process.process->priority].push(process);
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
	for (auto e : bitsMapTerminated) {
		e = 0;
	}
}

//METODY PRZEZNACZONE DO SHELLA
void Scheduler::displayActiveProcesses()
{
	std::cout << "Lista procesow aktywnych:" << std::endl;
	auto copyActiveProcesses = activeProcesses;

	for (auto e : copyActiveProcesses)
	{
		if (!e.empty()) std::cout << "Procesy o priorytecie " << e.front().process->priority << ":" << std::endl;
		while (!e.empty())
		{
			auto process = e.front();
			e.pop();

			std::cout << "Proces o nazwie: " << process.process->name << " i kwancie czasu: " << process.getRestTime() << std::endl;
		}
	}
}
void Scheduler::displayTerminatedProcesses() {

	std::cout << "Lista procesow przeterminowanych:" << std::endl;
	auto copyTerminatedProcesses = terminatedProcesses;

	for (auto e : copyTerminatedProcesses)
	{
		if (!e.empty()) std::cout << " Procesy o priorytecie " << e.front().process->priority << ":" << std::endl;
		while (!e.empty())
		{
			auto process = e.front();
			e.pop();

			std::cout << "Proces o nazwie: " << process.process->name << std::endl;
		}
	}
}
void Scheduler::displayActiveBitsMap() {
	std::cout << "MB procesow aktywnych:  ";
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
	std::cout << "MB procesow przeterminowanych:";
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
	std::cout << "Aktualnie posiadajacy procesor: " << runningProcess.process->name << " pozostaly kwant: " << runningProcess.getRestTime() << " i priorytecie " << runningProcess.process->priority << std::endl;
}

