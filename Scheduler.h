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
	//Znacznik mowiacy czy zostal ostatni proces, ktory otrzymal procesor, zostal wrzucony do kolejki procesow przeterminowanych
	bool lastTerminated;

	//Wektor kolejek procesow aktywnych	
	std::array <std::queue<Process>, 16> activeProcesses;
	//Wektor kolejek procesow przeterminowanych 
	std::array <std::queue<Process>, 16> terminatedProcesses;

	//Wektor bitowy procesow aktywnych (jedynka oznacz ze dany priorytet posiada reprezentanta)
	std::array <bool, 16> bitsMapActive;
	//Wektor bitowy procesow przeterminowanch (jedynka oznacz ze dany priorytet posiada reprezentanta)
	std::array <bool, 16> bitsMapTerminated;

	//Procesy o statusie waiting
	std::vector <Process> waitingProcesses;

public:

	//Wykorzystywane przez zarzadce procesami
	///Konstruktor mojej struktury
	Scheduler();
	///Dodawanie pierwszego procesu idle (najlepiej w konstruktorze "recznie"
	void addFirstProcess(PCB *process);
	///Dodawanie kazdego procesu poza idle
	void addProcess(PCB *process, unsigned int allNeedTime);
	///Nadawanie procesora (zwraca proces ktoremu przydzielilem procesor musisz go przekazac Ivanowi)
	unsigned int assignProcessor();
	///Usuwanie istniejacego procesu 
	void deleteProcess(unsigned int ID);
	///Przerzucenie z waiting do active
	void unsleep();
	///Dodawanie do plisty procesow waiting (przy Twojej funkcji sleep musisz wywolywac)
	void sleep(Process &process);

	//Wykorzystywane przeze mnie 
	void calculateFirstTimeCurrentPriority(Process &process, unsigned int allNeedTime);
	void calculateCurrentPriority(Process &process);
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
	int returnRunningProcess(){
		return runningProcess.process->ID;
	}
	
	
	//METODY PRZEZNACZONE DO SHELLA
	void displayActiveProcesses();
	void displayTerminatedProcesses();
	void displayActiveBitsMap();
	void displayTerminatedBitsMap();
	void displayRunningProcess();
	void displayWaitingProcesses();
	void displayAll();
};