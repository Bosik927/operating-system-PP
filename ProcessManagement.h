#pragma once
#include<ostream>
#include<iostream>
#include<string>
#include<list>
#include<random>
#include<time.h>
#include"ID_Manager.h"
#include"PCB.h"
#include"Scheduler.h"

class ProcessManagement {
private:
	std::list<PCB> Processes;
	void addFirstProcess(std::string path);
	Scheduler scheduler;
public:
	ProcessManagement() 
	{
		srand(time(0));//potrzebne do losowego priorytetu
		addFirstProcess("SCIEZKA PROCESU BEZCZYNNOSCI");
	}

	ID_Manager IdManager;
	PCB::processState GetState(int ID);
	int RandomPriority();
	//
	void SetState(int ID, PCB::processState newState);
	void print(int ID);
	int GetBasePriority(int ID);
	int GetCurrentPriority(int ID);
	void SetPriority(int ID, int Priority);
	int GetReg(int ID, char reg);
	void SetReg(int ID, char reg, int Value);
	int GetCommandCounter(int ID);
	void SetCommandCounter(int ID, int Val);
	std::string getNameFromId(int ID);
	int getIdFromName(std::string name);
	bool CheckNameUniqe(std::string name);

	PCB* getPCB(int ID);
	//JE�LI NIE ZNAJDZIE DANEGO PROCESU ZWRACA NULLPTR
	//KONIECZNA OBS�UGA B�EDU!!!
	
	

	//SCHEDULER
	void Run();
	void DisplayScheduler();
	void Sleep(int ID);
	void WakeUp(int ID);
	void DeleteProcess(int ID);
	int CreateProces(std::string Name, std::string Path, int BasePriority = 5);

	//SHELL
	PCB* AssignProcessor();
	//TU TE� OBS�UGA NULLPTR
	std::string DisplayAllProcesses();
	std::string DisplayProcessByName(std::string Name);
	std::string DisplayProcessByID(int ID);

};