#pragma once
#include<ostream>
#include<iostream>
#include<string>
#include<list>
#include<random>
#include<time.h>
#include"RAM.h"
#include"ID_Manager.h"
#include"PCB.h"
#include"Scheduler.h"

class ProcessManagement {
private:
	std::list<PCB> Processes;
	void addFirstProcess(std::string path);
	Scheduler scheduler;
	int lastRunningProcesID;
public:
	RAM *ram;

	ProcessManagement() 
	{
		//ram = nullptr;
	}
	ProcessManagement(RAM* ram) 
	{
		this->ram = ram;
		srand(time(0));//potrzebne do losowego priorytetu
		lastRunningProcesID = 0;
		addFirstProcess("idle.txt");
	}

	ID_Manager IdManager;
	PCB::processState GetState(int ID);
	int RandomPriority();
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
	//JEŒLI NIE ZNAJDZIE DANEGO PROCESU ZWRACA NULLPTR
	//KONIECZNA OBS£UGA B£EDU!!!

	//INTERPRETER
	PCB* GetRunningProcess();
	//OB£SUGA B£ÊDOW W CHUJ!!!

	//SCHEDULER
	//void Run();
	void DisplayScheduler();


	//SHELL
	//Nie podanie BasePriority, lub podanie 0 powoduje wybranie losowego priorytetu z grupy priorytetów normalnych
	std::string CreateProces(std::string Name, std::string Path, int BasePriority = 0);
	//Create i Delete zwracaj¹ wynik operacji, mo¿na je bezpoœrednio wyœwietlaæ na konsole w shellu
	std::string DeleteProcess(int ID);
	PCB* AssignProcessor();
	//TU TE¯ OBS£UGA NULLPTR
	std::string DisplayAllProcesses();
	std::string DisplayProcessByName(std::string Name);
	std::string DisplayProcessByID(int ID);

};