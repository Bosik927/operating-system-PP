#include"ProcessManagement.h"
#include<string>
#include<list>


//Tworzenie nowego pola PCB
int ProcessManagement::CreateProces(std::string Name, std::string Path, int BasePriority) {
	if (CheckNameUniqe(Name))
	{
		//B£¥D, POWIELONA NAZWA
		return -1;
	}
	else
	{
		int ID = IdManager.PickID();
		PCB temp(Name,BasePriority);
		temp.state = PCB::processState::newbie;
		//temp.name = Name;
		temp.ID = ID;
		temp.A = 0;
		temp.B = 0;
		temp.C = 0;
		temp.D = 0;
		//temp.basePriority = BasePriority;
		temp.commandCounter = 0;
		temp.blocked = 0;
		Processes.push_back(temp);
		SetState(ID, PCB::processState::ready);
	}
	return 0;
	//TRZEBA JAKOŒ DODAC KOD PROGRAMU DO RAMU
	//PATH - NAZWA LUB SCIEZKA PLIKU ZRODLOWEGO

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

//Tworzenie procesu bezczynnoœci
void ProcessManagement::addFirstProcess(std::string path)
{
	int ID = IdManager.PickID();
	PCB temp;
	temp.state = PCB::processState::newbie;
	temp.name = "idle";
	temp.ID = ID;
	temp.A = 0;
	temp.B = 0;
	temp.C = 0;
	temp.D = 0;
	temp.basePriority = 0;
	temp.commandCounter = 0;
	temp.blocked = 0;
	temp.state = PCB::processState::ready;
	Processes.push_back(temp);
	scheduler.addFirstProcess(this->getPCB(0));
	//TRZEBA JAKOŒ DODAC KOD PROGRAMU DO RAMU
}

//Usuwanie wybranego procesu z listy procesów
void ProcessManagement::DeleteProcess(int ID) {
	if(ID == 0) {
		//B£¥D NIE MOZNA USUNAC PROCESU BEZCZYNNOSCI
	}
	else {
		bool deleted = 0;
		for(std::list<PCB>::iterator iter = Processes.begin(); iter != Processes.end(); ++iter) {
			if(iter->ID == ID) 
			{
				scheduler.deleteProcess(ID);//metoda Stasia
				Processes.erase(iter);
				IdManager.ClearID(ID);
				deleted = 1;
				break;
			}
		}
		if(!deleted) {
			//B£¥D, BRAK PROCESU O PODANYM ID
		}
	}
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
			case PCB::processState::ready:
			{
				if (iter->blocked)
				{
					break;
					//nie mo¿na nadaæ stanu ready zablokowaneu procesowi
				}
				else
				{
					//sprawdzanie czy proces nie ma stanu gotowy
					if (iter->state != PCB::processState::ready)
					{
						//wrzucanie do kolejki procesów gotowych
						scheduler.addProcess(this->getPCB(ID), RandomPriority());//Losowanie tutaj priorytetu chyba jest bez sensu.
					}
					//nadawanie nowego stanu
					iter->state = newState;

				}
				break;
			}
			case PCB::processState::waiting:
			{
				if (iter->state == PCB::processState::ready)
				{
					//scheduler.sleep(ID); //chyba bez sensu tutaj
					iter->state = newState;
					
				}
				else
				{
					iter->state = newState;
				}
				break;
			}
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
//Usypia proces
void ProcessManagement::Sleep(int ID) 
{
	SetState(ID, PCB::processState::waiting);
	scheduler.sleep(ID);
}
//Budzi proces
void ProcessManagement::WakeUp(int ID) 
{
	SetState(ID, PCB::processState::ready);
	scheduler.unsleep(ID);
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

void ProcessManagement::Run()
{
	scheduler.assignProcessor();
}

PCB * ProcessManagement::AssignProcessor()
{
	int actvID;
	actvID = scheduler.assignProcessor();
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
