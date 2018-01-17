#include"ProcessManagement.h"
#include<string>
#include<list>


//Tworzenie nowego pola PCB, podanie 0 na BasePriority losuje priorytet
std::string ProcessManagement::CreateProces(std::string Name, std::string Path, int BasePriority) {
	if (CheckNameUniqe(Name))
	{
		//B£¥D, POWIELONA NAZWA
		return "Blad, proces o podanej nazwie juz istnieje\n";
	}
	else
	{

		int prior = BasePriority;
		if (prior == 0)
		{
			prior = RandomPriority();
		}
		PCB temp(Name, prior);
		temp.state = PCB::processState::newbie;
		temp.A = 0;
		temp.B = 0;
		temp.C = 0;
		temp.D = 0;
		temp.commandCounter = 0;
		temp.blocked = 0;
		int programLength = ram->exchangeFile.writeTo(temp.name, Path);//Stasiu to dla Ciebie :)
		if (programLength != -1)
		{
			int ID = IdManager.PickID();
			temp.ID = ID;
			Processes.push_back(temp);
			SetState(ID, PCB::processState::ready);
			scheduler.addProcess(this->getPCB(ID), programLength);
			ram->pageTables.push_back(PageTable(ram->exchangeFile.getRozmiar(temp.name), temp.name)); //Artur tu by³, tak musi byæ
			return "Utworzono proces: \"" + Name + "\" o identyfikatorze: " + std::to_string(ID) + " i priorytecie wg. Windows: " + std::to_string(prior) + "\n";
		}
		else
		{
			return "Nie udalo sie pobrac kodu programu, tworzenie procesu zostalo przerwane\n";
		}
	}
	return "Nieznany blad przy tworzeniu procesu\n";

}

//Losowy priorytet z grupy priorytetów normalnych 1-7
int ProcessManagement::RandomPriority()
{
	return rand()%7+1;
}

//Sprawdza unikalnoœæ nazwy procesu; 0 - unikalna, 1 - powtarza siê
bool ProcessManagement::CheckNameUniqe(std::string Name)
{
	for (std::list<PCB>::iterator iter = Processes.begin(); iter != Processes.end(); ++iter) {
		if (iter->name == Name)
		{
			return 1;
		}
	}
	return 0;
}

//Tworzenie procesu bezczynnoœci, nadaje mu ID 0, i stan active
void ProcessManagement::addFirstProcess(std::string path)
{
	int ID = IdManager.PickID();
	PCB temp("idle", 0);
	temp.state = PCB::processState::newbie;
	temp.ID = ID;
	temp.A = 0;
	temp.B = 0;
	temp.C = 0;
	temp.D = 0;
	//temp.basePriority = 0;
	temp.commandCounter = 0;
	temp.blocked = 0;
	temp.state = PCB::processState::ready;
	Processes.push_back(temp);
	scheduler.addFirstProcess(this->getPCB(0));
	SetState(0, PCB::processState::active);
	ram->exchangeFile.writeTo(temp.name, path);
	ram->pageTables.push_back(PageTable(ram->exchangeFile.getRozmiar(temp.name), temp.name));
}

//Usuwanie wybranego procesu z listy procesów
std::string ProcessManagement::DeleteProcess(int ID) {
	if(ID == 0) {
		return "Blad, usuniecie procesu bezczynnosci jest niemozliwe!\n";
	}
	else {
		bool deleted = 0;
		for(std::list<PCB>::iterator iter = Processes.begin(); iter != Processes.end(); ++iter)
		{
			if(iter->ID == ID) 
			{
				scheduler.deleteProcess(ID);//metoda Stasia
				ram->deleteProcessData(iter->name);
				Processes.erase(iter);
				IdManager.ClearID(ID);
				deleted = 1;
				return "Usunieto proces o identyfikatorze: " + std::to_string(ID) + "\n";
			}
		}
		if(!deleted) {
			return "Nie znaleziono procesu o podanym ID\n";
		}
	}
	return "Nieznany blad przy usuwaniu procesu\n";
}
//Pobieranie stanu wybranego procesu
PCB::processState ProcessManagement::GetState(int ID) 
{
	for(std::list<PCB>::iterator iter = Processes.begin(); iter != Processes.end(); ++iter) {
		if(iter->ID == ID) {
			return iter->state;
		}
	}
	return PCB::processState::err;
}

//Nadawanie stanu procesu
void ProcessManagement::SetState(int ID, PCB::processState newState) {
	for(std::list<PCB>::iterator iter = Processes.begin(); iter != Processes.end(); ++iter) {
		if(iter->ID == ID) 
		{
			switch (newState)
			{
			default:
				iter->state = newState;
				break;
			}
			break;
		}
	}
}

//Drukowanie zawartoœci PCB procesu o podanym ID
void ProcessManagement::print(int ID) {
	for(std::list<PCB>::iterator iter = Processes.begin(); iter != Processes.end(); ++iter) {
		if(iter->ID == ID) {
			std::cout << iter->display();
			break;
		}
	}
}
//Pobieranie priorytetu bazowego
int ProcessManagement::GetBasePriority(int ID) {
	for(std::list<PCB>::iterator iter = Processes.begin(); iter != Processes.end(); ++iter) {
		if(iter->ID == ID) {
			return iter->basePriority;
		}
	}
	return -1;
}
//Pobieranie aktualnego priorytetu
int ProcessManagement::GetCurrentPriority(int ID) {
	for(std::list<PCB>::iterator iter = Processes.begin(); iter != Processes.end(); ++iter) {
		if(iter->ID == ID) {
			return iter->priority;
		}
	}
	return -1;
}
//Nadawanie priorytetu
void ProcessManagement::SetPriority(int ID, int Priority) {
	for(std::list<PCB>::iterator iter = Processes.begin(); iter != Processes.end(); ++iter) {
		if(iter->ID == ID) {
			iter->priority = Priority;
		}
	}
}
//Pobieranie zawartoœci rejestrów
int ProcessManagement::GetReg(int ID, char reg) {
	for(std::list<PCB>::iterator iter = Processes.begin(); iter != Processes.end(); ++iter) {
		if(iter->ID == ID) {
			switch(reg) {
				case 'A':
					return iter->A;
					break;

				case 'B':
					return iter->B;
					break;

				case 'C':
					return iter->C;
					break;
				case 'D':
					return iter->D;
					break;

				default:
					return -1;
					break;
			}
		}
	}
	return -1;
}
//Nadawanie zawartoœci rejestrom
void ProcessManagement::SetReg(int ID, char reg, int Value) {
	for(std::list<PCB>::iterator iter = Processes.begin(); iter != Processes.end(); ++iter) {
		if(iter->ID == ID) {
			switch(reg) {
				case 'A':
					iter->A = Value;
					break;

				case 'B':
					iter->B = Value;
					break;

				case 'C':
					iter->C = Value;
					break;

				case 'D':
					iter->D = Value;
					break;

				default:
					break;
			}
		}
	}
}
//Pobieranie wartoœci licznika komend
int ProcessManagement::GetCommandCounter(int ID) {
	for(std::list<PCB>::iterator iter = Processes.begin(); iter != Processes.end(); ++iter) {
		if(iter->ID == ID) {
			return iter->commandCounter;
		}
	}
	return -1;
}
//Ustawia wartoœæ licznika komend
void ProcessManagement::SetCommandCounter(int ID, int Val) {
	for(std::list<PCB>::iterator iter = Processes.begin(); iter != Processes.end(); ++iter) {
		if(iter->ID == ID) {
			iter->commandCounter = Val;
		}
	}
}
//Zwraca nazwê na podstawie identyfikatora
std::string ProcessManagement::getNameFromId(int ID) {
	for(std::list<PCB>::iterator iter = Processes.begin(); iter != Processes.end(); ++iter) {
		if(iter->ID == ID) {
			return iter->name;
		}
	}
	return "err";
}
//Zwraca identyfikator procesu na podstawie nazwy
int ProcessManagement::getIdFromName(std::string name) {
	for(std::list<PCB>::iterator iter = Processes.begin(); iter != Processes.end(); ++iter) {
		if(iter->name == name) {
			return iter->ID;
		}
	}
	return -1;
}

//Zwraca wskaŸnik do PCB
//JEŒLI NIE ZNAJDZIE DANEGO PROCESU ZWRACA NULLPTR
//KONIECZNA OBS£UGA B£EDU!!!
PCB * ProcessManagement::getPCB(int ID) {
	PCB* temp = nullptr;
	for(std::list<PCB>::iterator iter = Processes.begin(); iter != Processes.end(); ++iter) {
		if(iter->ID == ID) {
			temp = &(*iter);
		}
	}
	return temp;
}

void ProcessManagement::DisplayScheduler()
{
	scheduler.displayActiveBitsMap();
	scheduler.displayActiveProcesses();
	scheduler.displayRunningProcess();
	scheduler.displayTerminatedBitsMap();
	scheduler.displayTerminatedProcesses();
}

PCB * ProcessManagement::GetRunningProcess()
{
	int actvID = scheduler.returnRunningProcess();
	return getPCB(actvID);
}

//void ProcessManagement::Run()//Czy to jest potrzebne w ogole?
//{
//	scheduler.assignProcessor();
//}

PCB * ProcessManagement::AssignProcessor()
{
	
	//int outdatedID = scheduler.returnRunningProcess();
	if (GetState(lastRunningProcesID) == PCB::processState::active)
	{
		SetState(lastRunningProcesID, PCB::processState::ready);
	}
	int actvID = scheduler.assignProcessor();
	lastRunningProcesID = actvID;
	SetState(actvID, PCB::processState::active);
	return getPCB(actvID);
}


std::string ProcessManagement::DisplayAllProcesses()
{
	std::string all;
	for (PCB process : Processes)
	{
		all += process.display();
	}
	return all;
}

std::string ProcessManagement::DisplayProcessByName(std::string Name)
{
	for (std::list<PCB>::iterator iter = Processes.begin(); iter != Processes.end(); ++iter) {
		if (iter->name == Name) {
			return iter->display();
		}
	}
	return "Nie znaleziono procesu o danej nazwie\n";
}

std::string ProcessManagement::DisplayProcessByID(int ID)
{
	for (std::list<PCB>::iterator iter = Processes.begin(); iter != Processes.end(); ++iter) {
		if (iter->ID == ID) {
			return iter->display();
		}
	}
	return "Nie znaleziono procesu o danym ID\n";
}
