#pragma once
#include "Interpreter.h"
Rozkazy convert(const string& operacja) // Funkcja dla konwersji rozkazow dla switcha
{
	if (operacja == "AD") return AD;
	else if (operacja == "AX") return AX;
	else if (operacja == "SB") return SB;
	else if (operacja == "MU") return MU;
	else if (operacja == "MX") return MX;
	else if (operacja == "MV") return MV;
	else if (operacja == "MZ") return MZ;
	else if (operacja == "MO") return MO;
	else if (operacja == "MY") return MY;
	else if (operacja == "JP") return JP;
	else if (operacja == "JZ") return JZ;
	else if (operacja == "CF") return CF;
	else if (operacja == "WF") return WF;
	else if (operacja == "DF") return DF;
	else if (operacja == "RF") return RF;
	else if (operacja == "AF") return AF;
	else if (operacja == "FC") return FC;
	else if (operacja == "CP") return CP;
	else if (operacja == "DP") return DP;
	else if (operacja == "RP") return RP;
	else if (operacja == "RM") return RM;
	else if (operacja == "SM") return SM;
	else if (operacja == "HL") return HL;
}
bool Interpreter::isLabel(string &program)
{
	if (program[program.size() - 2] == ':')
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Interpreter::run(PCB* PCBbox)
{
	program = ram->getCommand(PCBbox->commandCounter,PCBbox->name);
	if (!program.size())
	{
		cout << "Nie udalo sie pobrac rozkazu!" << endl;
	}
	if (isLabel(program))
	{
		PCBbox->commandCounter += program.size();
		label = PCBbox->commandCounter;
	}
	else
	{
		PCBbox->commandCounter += program.size();
		program.erase(program.end() - 1, program.end());
		switch (convert(program.substr(0, 2)))
		{
		case AD:
		{
			if (program.substr(2, 1) == " ")
			{
				if (program.substr(3, 1) == "B")
				{
					processmanagement->SetReg(PCBbox->ID, 'A', processmanagement->GetReg(PCBbox->ID, 'A')+processmanagement->GetReg(PCBbox->ID, 'B'));
				}
				else if (program.substr(3, 1) == "C")
				{
					processmanagement->SetReg(PCBbox->ID, 'A', processmanagement->GetReg(PCBbox->ID, 'A')+processmanagement->GetReg(PCBbox->ID, 'C'));
				}
				else if (program.substr(3, 1) == "D")
				{
					processmanagement->SetReg(PCBbox->ID, 'A', processmanagement->GetReg(PCBbox->ID, 'A')+processmanagement->GetReg(PCBbox->ID, 'D'));
				}
			}
			else
			{
				cout << "Niepoprawny rozkaz" << endl;
			}
			break;
		}
		case AX:
		{
			if (program.substr(2, 1) == " ")
			{
				int liczba = 0;
				liczba = atoi(program.substr(4, program.size() - 4).c_str());
				if (program.substr(3, 1) == "A")
				{
					processmanagement->SetReg(PCBbox->ID, 'A', processmanagement->GetReg(PCBbox->ID, 'A')+liczba);
				}
				else if (program.substr(3, 1) == "B")
				{
					processmanagement->SetReg(PCBbox->ID, 'B', processmanagement->GetReg(PCBbox->ID, 'B')+liczba);
				}
				else if (program.substr(3, 1) == "C")
				{
					processmanagement->SetReg(PCBbox->ID, 'C', processmanagement->GetReg(PCBbox->ID, 'C')+liczba);
				}
				else if (program.substr(3, 1) == "D")
				{
					processmanagement->SetReg(PCBbox->ID, 'D', processmanagement->GetReg(PCBbox->ID, 'D')+liczba);
				}
			}
			else
			{
				cout << "Niepoprawny rozkaz" << endl;
			}
			break;
		}

		case SB:
		{
			if (program.substr(2, 1) == " ")
			{
				int liczba = 0;
				liczba = atoi(program.substr(4, program.size() - 4).c_str());
				if (program.substr(3, 1) == "A")
				{
					processmanagement->SetReg(PCBbox->ID, 'A', processmanagement->GetReg(PCBbox->ID, 'A')-liczba);
				}
				else if (program.substr(3, 1) == "B")
				{
					processmanagement->SetReg(PCBbox->ID, 'B', processmanagement->GetReg(PCBbox->ID, 'B')-liczba);
				}
				else if (program.substr(3, 1) == "C")
				{
					processmanagement->SetReg(PCBbox->ID, 'C', processmanagement->GetReg(PCBbox->ID, 'C')-liczba);
				}
			}
			else
			{
				cout << "Niepoprawny rozkaz" << endl;
			}
			break;
		}
		case MU:
		{
			if (program.substr(2, 1) == " ")
			{
				if (program.substr(3, 1) == "A")
				{
					processmanagement->SetReg(PCBbox->ID, 'A', processmanagement->GetReg(PCBbox->ID, 'A')*processmanagement->GetReg(PCBbox->ID, 'A'));
				}
				else if (program.substr(3, 1) == "B")
				{
					processmanagement->SetReg(PCBbox->ID, 'A', processmanagement->GetReg(PCBbox->ID, 'A')*processmanagement->GetReg(PCBbox->ID, 'B'));
				}
				else if (program.substr(3, 1) == "C")
				{
					processmanagement->SetReg(PCBbox->ID, 'A', processmanagement->GetReg(PCBbox->ID, 'A')*processmanagement->GetReg(PCBbox->ID, 'C'));
				}
				else if (program.substr(3, 1) == "D")
				{
					processmanagement->SetReg(PCBbox->ID, 'A', processmanagement->GetReg(PCBbox->ID, 'A')*processmanagement->GetReg(PCBbox->ID, 'D'));
				}
			}
			else
			{
				cout << "Niepoprawny rozkaz" << endl;
			}
			break;

		}
		case MX:
		{
			if (program.substr(2, 1) == " ")
			{
				int liczba = 0;
				liczba = atoi(program.substr(4, program.size() - 4).c_str());
				if (program.substr(3, 1) == "A")
				{
					processmanagement->SetReg(PCBbox->ID, 'A', processmanagement->GetReg(PCBbox->ID, 'A')*liczba);
				}
				else if (program.substr(3, 1) == "B")
				{
					processmanagement->SetReg(PCBbox->ID, 'B', processmanagement->GetReg(PCBbox->ID, 'B')*liczba);
				}
				else if (program.substr(3, 1) == "C")
				{
					processmanagement->SetReg(PCBbox->ID, 'C', processmanagement->GetReg(PCBbox->ID, 'C')*liczba);
				}
				else if (program.substr(3, 1) == "D")
				{
					processmanagement->SetReg(PCBbox->ID, 'D', processmanagement->GetReg(PCBbox->ID, 'D')*liczba);
				}
			}
			else
			{
				cout << "Niepoprawny rozkaz" << endl;
			}
			break;
		}
		case MV:
		{
			if (program.substr(2, 1) == " ")
			{
				if (program.substr(3, 1) == "B")
				{
					processmanagement->SetReg(PCBbox->ID, 'B', processmanagement->GetReg(PCBbox->ID, 'A'));
				}
				else if (program.substr(3, 1) == "C")
				{
					processmanagement->SetReg(PCBbox->ID, 'C', processmanagement->GetReg(PCBbox->ID, 'A'));
				}
				else if (program.substr(3, 1) == "D")
				{
					processmanagement->SetReg(PCBbox->ID, 'D', processmanagement->GetReg(PCBbox->ID, 'A'));
				}
			}
			else
			{
				cout << "Niepoprawny rozkaz" << endl;
			}
			break;
		}
		case JP:
		{
			if (program.size() == 2)
			{
				if (processmanagement->GetReg(PCBbox->ID, 'D') != 0) // processmanagement.GetReg(PCBbox.ID, 'D') != 0
				{
					processmanagement->SetReg(PCBbox->ID, 'D', processmanagement->GetReg(PCBbox->ID, 'D') - 1);
					PCBbox->commandCounter = label;
				}
				break;
			}
			else
			{
				int liczba = 0;
				liczba = atoi(program.substr(4, program.size() - 4).c_str());
				PCBbox->commandCounter = liczba;
				break;
			}
		}
		case CF:
		{
			if (program.substr(2, 1) == " ")
			{
				string name;
				name = program.substr(3, program.size() - 3).c_str();
				disc->tworzeniaPliku(name);
				disc->otworzPlik(name, PCBbox);
			}
			else
			{
				cout << "Niepoprawny rozkaz" << endl;
			}
			break;
		}
		case WF:
		{
			if (program.substr(2, 1) == " ")
			{
				string name, data;
				name = program.substr(3, program.find(" ", 4) - 3).c_str(); // wyciagniecie nazwy z rozszerzeniem
				data = program.substr(program.find(" ", 3) + 1, program.size() - program.find(" ", 4)).c_str(); // wyciagniecie danych
				disc->wpisywanieDoPliku(name,data, PCBbox);
			}
			else
			{
				cout << "Niepoprawny rozkaz" << endl;
			}
			break;
		}
		case DF:
		{
			if (program.substr(2, 1) == " ")
			{
				string name;
				name = program.substr(3, program.size() - 3).c_str();
				disc->usuwaniePliku(name, PCBbox);
			}
			else
			{
				cout << "Niepoprawny rozkaz" << endl;
			}
			break;
		}
		case RF:
		{
			if (program.substr(2, 1) == " ")
			{
				string name, newname;
				name = program.substr(3, program.find(" ", 4) - 3).c_str(); // wyciagniecie nazwy z rozszerzeniem
				newname = program.substr(program.find(" ", 3) + 1, program.size() - program.find(" ", 4)).c_str(); // wyciagniecie danych
				disc->zmianaNazwy(name,newname, PCBbox);
			}
			else
			{
				cout << "Niepoprawny rozkaz" << endl;
			}
			break;
		}
		case AF:
		{
			if (program.substr(2, 1) == " ")
			{
				string name, data;
				name = program.substr(3, program.find(" ", 4) - 3).c_str(); // wyciagniecie nazwy z rozszerzeniem
				data = program.substr(program.find(" ", 3) + 1, program.size() - program.find(" ", 4)).c_str(); // wyciagniecie danych
				disc->dopiszDoPliku(name,data, PCBbox);
			}
			else
			{
				cout << "Niepoprawny rozkaz" << endl;
			}
			break;
		}
		case FC:
		{
			if (program.substr(2, 1) == " ")
			{
				string name;
				name = program.substr(3, program.size() - 3).c_str();
				disc->zamknijPlik(name, PCBbox);
			}
			else
			{
				cout << "Niepoprawny rozkaz" << endl;
			}
			break;
		}
		case CP:
		{
			if (program.substr(2, 1) == " ")
			{
				string name, path;
				name = program.substr(3, program.find(" ", 4) - 3).c_str(); // wyciagniecie nazwy
				path = program.substr(program.find(" ", 3) + 1, program.size() - program.find(" ", 4)).c_str(); // wyciagniecie sciezki																								// processmanagement.CreateProcess(name,path);
				processmanagement->CreateProces(name,path,5);
			}
			else
			{
				cout << "Niepoprawny rozkaz" << endl;
			}
			break;
		}
		case DP:
		{
			if (program.substr(2, 1) == " ")
			{
				string name;
				int ID;
				name = program.substr(3, program.size() - 3).c_str();
				ID=processmanagement->getIdFromName(name);
				processmanagement->DeleteProcess(ID);
			}
			else
			{
				cout << "Niepoprawny rozkaz" << endl;
			}
			break;
		}

		// Run proces jest niepotrzebnie w naszym systemie
		/*
		case RP:
		{
			if (program.substr(2, 1) == " ")
			{
				string name;
				int ID;
				name = program.substr(3, program.size() - 3).c_str();
				// ID=Processes.getIdFromName(name); 
				// processesmanagment.setState(ID,1);
				// processesmanagment.SetPriority(ID, MAKSYMALNY_PRIORYTET + 1);
			}
			else
			{
				cout << "Niepoprawny rozkaz" << endl;
			}
			break;
		}
		*/
		case RM:
		{
			if (program.substr(2, 1) == " ")
			{
				string name;
				int ilosc_znakow=0;
				name = program.substr(3, program.find(" ", 4) - 3).c_str();
				ilosc_znakow = atoi(program.substr(program.find(" ", 3) + 1, program.size() - program.find(" ", 4)).c_str());
				komunikacja->read(name,ilosc_znakow); 
			}
			else
			{
				cout << "Niepoprawny rozkaz" << endl;
			}
			break;
		}
		case SM:
		{
			if (program.substr(2, 1) == " ")
			{
				string name, data;
				name = program.substr(3, program.find(" ", 4) - 3).c_str(); // wyciagniecie nazwy
				data = program.substr(program.find(" ", 3) + 1, program.size() - program.find(" ", 4)).c_str(); // wyciagniecie sciezki
				komunikacja->write(name,data); 
			}
			else
			{
				cout << "Niepoprawny rozkaz" << endl;
			}
			break;
		}
		case HL:
		{
			processmanagement->DeleteProcess(PCBbox->ID);
			cout << "KONIEC PROCESU" << endl;
			break;
		}
		default:
		{
			cout << "Nie rozpoznano rozkazu." << endl;
			break;
		}
		}
	}
}
