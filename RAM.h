#pragma once
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <fstream>
#include <array>

//exchangeFile

struct struktura
{
	std::string procName;
	std::array <char, 16> data;
	int rozmiar;
};

class ExchangeFile {
public:
	std::vector<struktura> exchangeFile;
	std::vector<std::string> pomoc;
	int ile_potrzeba_ramek2(int ile) //zwraca liczbê wymaganych ramek/stronnic wymaganych do przechowania zadanej iloœci znaków
	{
		if (ile <= 0)
		{
			return 0;
		}
		int iloœæ_ramek = ile / 16;
		if (ile % 16 != 0)
		{
			iloœæ_ramek++;
		}

		return iloœæ_ramek;
	}

	int writeTo(std::string &processName, std::string &fileName)
	{
		int licznikRozkazow = 0;
		std::ifstream program;
		program.open(fileName);
		std::string wiersz;
		std::string buff;
		if (!program) return -1;
		while (std::getline(program, wiersz))
		{
			pomoc.push_back(wiersz);
			buff += wiersz;
			buff += "\n";
			licznikRozkazow++;
		}
		while (buff.size() % 16 != 0)
		{
			buff.push_back(' ');
		}
		int ilosc_stron = ile_potrzeba_ramek2(pomoc.size() / 16); //do poprawy na ile_potrzeba_ramek
		struktura nowa;
		for (int i = 0; i * 16 < buff.size(); i++)
		{
			for (int j = 0; j < 16; j++)
			{
				nowa.procName = processName;
				nowa.data[j] = buff[i * 16 + j];

			}
			nowa.rozmiar = buff.size();
			exchangeFile.push_back(nowa);
		}

		return licznikRozkazow;
	}

	const char *readFrom(std::string &processName, int pageIndex, int indexInPage)
	{
		for (int i = 0; i < exchangeFile.size(); i++)
		{
			if (exchangeFile[i].procName == processName)
			{
				for (int j = 0; j < exchangeFile.size() - i; j++)
				{
					if (j == pageIndex) return exchangeFile[i+j].data.data();
				}
			}
		}
		

		// ???? JESZCZE OBS£UGA B£ÊDU ????
	}

	void saveTo(std::string &processName, char data[16], int pageIndex)
	{ //zapisywanie ca³ej strony

		for (int j = 0; j < 16; j++)
		{
			exchangeFile[pageIndex].data[j] = data[j];
		}


		// ???? JESZCZE OBS£UGA B£ÊDU ????
	}

	void showContent()
	{
		std::cout << "Zawartosc pliku wymiany: ";
		for (struktura i : exchangeFile)
		{
			std::string buff(i.data.data());
			std::string pom = "[";
			buff.erase(buff.begin() + 16, buff.end());
			for (int i = 0; i < 16; i++)
			{
				if (buff[i] == '\n')
				{
					pom += " ";
				}
				else pom += buff[i];
			}
			buff = "]     proces: ";
			pom += buff;
			buff = i.procName;
			pom += buff;
			std::cout << pom << std::endl;
		}
	}

	void deleteData(std::string &processName)
	{
		int j = 0;
		std::vector<int> pom;
		for (struktura i : exchangeFile)
		{
			if (i.procName == processName)
			{
				pom.push_back(j);
			}
		 	j++;
		}
		if (pom.size() > 0)
		{
			for (int i = pom.size()-1; i>=0;i--)
			{
				exchangeFile.erase(exchangeFile.begin() + pom[i]);
			}
		}
	}

	int getRozmiar(std::string processName)
	{
		for (auto i : exchangeFile)
		{
			if (i.procName == processName) return i.rozmiar;
		}
	}
};


//pageTable

class PageTable
{
public:
	int* framesNumber; //w jakich ramkach jest dana strona programu
	bool* inRAM; // czy jest w ramie
	std::string processName; //nr procesu, który jest w RAMie
	int sizeOfTable;
	PageTable() {}
	PageTable(int processDataSize, std::string procName) // ???? Potrzebujê pobraæ sk¹dœ rozmiar procesu ????
	{
		int count;
		// obliczanie ile stron zajmuje dany program
		if (processDataSize % 16 == 0)
			count = processDataSize / 16;
		else
			count = processDataSize / 16 + 1;
		// ustawianie odpowiednich wartosci
		framesNumber = new int[count];
		inRAM = new bool[count];
		processName = procName;
		sizeOfTable = count;
		// wypelnienie
		for (int i = 0; i < count; i++)
		{
			framesNumber[i] = -1;
			inRAM[i] = false;
			// System.out.println(framesNumber[i] +" "+ inRAM[i]+"A");
		}
	}

	//zwraca pozycjê stronicy w RAMie lub -1, gdy stronicy nie ma w RAMie
	int getPositionInRam(int pageNumber)
	{
		if (inRAM[pageNumber] == true)
		{
			return framesNumber[pageNumber];
		}
		else
			return -1;
	}

	// zwraca nr stronicy ktora jest w danej ramce
	int getIndex(int pageInRam)
	{
		for (int i = 0; i < sizeOfTable; i++) {
			if (framesNumber[i] == pageInRam)
				return i;
		}
		return -1;
	}
	// wypisuje tablice stronic
	void writePageTable()
	{
		for (int i = 0; i < sizeOfTable; i++)
			std::cout << framesNumber[i] << " " << inRAM[i] << std::endl; // ???? Pewnie do poprawy ????
	}
};

struct Ramka
{
public:
	int adres_poczatkowy;
	int adres_koncowy;
	int nr_ramki;
	bool bit_odniesienia;
	bool bit_modyfikacji;

	Ramka()
	{
		bit_odniesienia = 0;
		bit_modyfikacji = 0;
	}
};

//pageTable

class RAM
{
private:
public:

	char *ram = new char[256];
	std::vector<Ramka> framesTable;
	std::string *processNameInFrame = new std::string[16]; //NO NIBY SPOKO ZMIENNA, ALE POWINIENEM TO CHYBA POBIERAÆ OD ADAMA
	std::queue<int> FIFO;
	ExchangeFile exchangeFile;
	//tabela stron
	std::vector<PageTable> pageTables;
	std::stack<int> freeFrames;
public:
	// konstruktor, ustawienie podstawowych parametrow
	RAM() {
		for (int i = 0; i < 16; i++) {
			processNameInFrame[i] = "";
			for (int j = 0; j < 16; j++)
				ram[i *16+ j] = ' ';

		}
		inicjalizacja_tabeli_ramek();
		inicjalizacja_stosu_ramek();
	}
	void inicjalizacja_tabeli_ramek() //inicjalizuje liste ramek aby zawiera³a odpowiednie wskazania na komorki pamieci
	{
		for (int i = 0; i < 16; i++)
		{
			Ramka ramka;
			ramka.adres_poczatkowy = i * 16;
			ramka.adres_koncowy = i * 16 + 16 - 1;
			ramka.nr_ramki = i;
			framesTable.push_back(ramka);
			FIFO.push(i);
		}
	}

	void inicjalizacja_stosu_ramek()
	{
		for (int i = 15; i >= 0; i--)
		{
			freeFrames.push(i);
		}
	}

	char *odczytaj_ramkê(int ramka) //odczytuje ramkê o zadanym numerze i zwraca jej zawartoœæ w stringu
	{
		char *bufor = new char[16]; //tworzê bufor na odczytane dane

		for (int i = 0; i < 16; i++)
		{
			bufor[i] = ram[ramka * 16 + i]; //odczytujê ca³¹ ramkê
		}
		return bufor; //zwracam stringa
	}

	std::string zwroc_rozkaz(int ramka, int adres, std::string procName)
	{
		std::string temp = ""; //tworzê bufor na odczytane dane

		for (int i = adres%16; i < 16; i++)
		{
			if (ram[ramka * 16 + i] == '\n')
			{
				temp.push_back('\n');
				return temp;
			}
			temp.push_back(ram[ramka * 16 + i]); //odczytujê rozkaz
		}
		temp += (getCommand(adres + temp.size(), procName));
		return temp;
	}

	void zapisz_ramkê(int numer_ramki, std::string znaki) //zapisuje znaki w konkretnej ramce (odpowiadaj¹cej dostarczonemu segmentowi); nie zmienia bitu u¿ywania na true; jest to zmieniane przy wyszukiwaniu wolnej ramki
	{
		int adres = numer_ramki * 16;

		for (int i = 0; i < znaki.size(); i++)
		{
			ram[adres + i] = znaki[i];
		}
	}


	//przydzielanie pamiêci

	int ramka_ze_stosu()
	{
		int ramka = freeFrames.top();
		freeFrames.pop();
		framesTable[ramka].bit_odniesienia = true;
		return ramka;
	}

	void zwolnij_ramkê(int ramka)
	{
		freeFrames.push(ramka); //oznaczam ramkê jako woln¹
								//z kolejki FIFO muszê teraz usun¹æ tê ramkê:
		for (int i = 0; i < pageTables.size(); i++)
		{
			if (pageTables[i].processName == processNameInFrame[ramka])
			{
				pageTables[i].inRAM[pageTables[i].getIndex(ramka)] = false;
				if (framesTable[ramka].bit_modyfikacji == 1) exchangeFile.saveTo(processNameInFrame[ramka], odczytaj_ramkê(ramka), pageTables[i].getIndex(ramka));
			}
				
		}// tutaj do poprawienia nadpisywanie pliku wymiany

		std::queue<int> bufor; //tworzê tymczasow¹ kolejkê pomocnicz¹
		framesTable[ramka].bit_modyfikacji = 0;
		framesTable[ramka].bit_odniesienia = 0;
		FIFO.push(FIFO.front());
		FIFO.pop();
		//bufor.push(ramka);
		// odwracam kolejkê
		//while (bufor.size() > 0)
		//{
		//	FIFO.push(bufor.front());
		//	bufor.pop();
		//}
	}


	int ktora_ramke_zwolnic()
	{
		int pom;
		do
		if (framesTable[FIFO.front()].bit_odniesienia == 0)
		{
			pom = FIFO.front();
			FIFO.push(FIFO.front());
			FIFO.pop();
			return pom;
		}
		else
		{
			framesTable[FIFO.front()].bit_odniesienia = 0;
			FIFO.push(FIFO.front());
			FIFO.pop();
		}
		while (true);
		//int pierwsza_ramka = FIFO.front();
		//if (framesTable[pierwsza_ramka].bit_modyfikacji == 0 && framesTable[pierwsza_ramka].bit_odniesienia == 0)
		//{
		//	FIFO.push(FIFO.front());
		//	FIFO.pop();
		//	return pierwsza_ramka;
		//}
		//else
		//{
		//	framesTable[pierwsza_ramka].bit_odniesienia = 0;
		//	FIFO.push(pierwsza_ramka);
		//	FIFO.pop();
		//	while (FIFO.front() != pierwsza_ramka)
		//	{
		//		if (framesTable[FIFO.front()].bit_odniesienia == 0 && framesTable[FIFO.front()].bit_modyfikacji == 0)
		//		{
		//			pierwsza_ramka = FIFO.front();
		//			FIFO.push(FIFO.front());
		//			FIFO.pop();
		//			return pierwsza_ramka;
		//		}
		//		else
		//		{
		//			framesTable[FIFO.front()].bit_odniesienia = 0;
		//			FIFO.push(FIFO.front());
		//			FIFO.pop();
		//		}
		//	}

		//	if (framesTable[FIFO.front()].bit_odniesienia == 0 && framesTable[FIFO.front()].bit_modyfikacji == 0) 
		//	{
		//		pierwsza_ramka = FIFO.front();
		//		FIFO.push(FIFO.front());
		//		FIFO.pop();
		//		return pierwsza_ramka;
		//	}
		//	else
		//	{
		//		while (FIFO.front() != pierwsza_ramka)
		//		{
		//			if (framesTable[FIFO.front()].bit_odniesienia == 0 && framesTable[FIFO.front()].bit_modyfikacji == 0) 
		//			{
		//				pierwsza_ramka = FIFO.front();
		//				FIFO.push(FIFO.front());
		//				FIFO.pop();
		//				return pierwsza_ramka;
		//			}
		//			else
		//			{
		//				FIFO.push(FIFO.front());
		//				FIFO.pop();
		//			}
		//		}
		//	}
		//	
		//}
		//return FIFO.front();
	}

	void writeToRam(int index, const char content[16]) {
		for (int i = 0; i < 16; i++) {
			ram[index * 16 + i] = content[i];
		}
	}

	void strona_w_ramke(int nrStrony, std::string procName)
	{
		if (freeFrames.size() <= 0) zwolnij_ramkê(ktora_ramke_zwolnic());
		for (int i = 0; i < pageTables.size(); i++)
		{
			if (pageTables[i].processName == procName)
			{
				processNameInFrame[freeFrames.top()] = procName;
				pageTables[i].framesNumber[nrStrony] = freeFrames.top();
				framesTable[freeFrames.top()].bit_odniesienia = 1;
				pageTables[i].inRAM[nrStrony] = true;
				freeFrames.pop();
				writeToRam(pageTables[i].framesNumber[nrStrony], exchangeFile.readFrom(procName, nrStrony, 0));
			}
		}
	}

	std::string getCommand(int programCounter, std::string &processName)
	{
		PageTable ktora_tablica;
		int pageIndex;
		if ((programCounter) % 16 == 0) pageIndex = ((programCounter + 1) / 16);
		else pageIndex = ((programCounter) / 16);
		for (auto a : pageTables)
		{
			if (processName == a.processName)
			{
				ktora_tablica = a;
				break;
			}
		}
		if (ktora_tablica.inRAM[pageIndex])
		{
			framesTable[ktora_tablica.framesNumber[pageIndex]].bit_odniesienia = 1;
			return zwroc_rozkaz(ktora_tablica.framesNumber[pageIndex], programCounter, processName);
		}

		else strona_w_ramke(pageIndex, ktora_tablica.processName);
		return zwroc_rozkaz(ktora_tablica.framesNumber[pageIndex], programCounter, processName);
	}

	// usuwanie danego procesu z pamieci
	void deleteProcessData(std::string procName) {
		// usuniecie danych z pamieci ram
		// ??? Do poprawienia
		std::vector<int> pom;
		PageTable ktora_tablica;
		int x = 0;
		for (auto a : pageTables)
		{
			if (procName == a.processName)
			{
				pom.push_back(x);
			}
			x++;
		}
		if (pom.size() > 0)
		{
			for (int i = pom.size() - 1; i >= 0; i--)
			{
				pageTables.erase(pageTables.begin() + pom[i]);
			}
		}
		for (int i = 0; i < 16; i++) {
			if (processNameInFrame[i] == (procName)) {
				freeFrames.push(i);
				processNameInFrame[i] == "";
				for (int j = 0; j < 16; j++)
					ram[i * 16 + j] = ' ';
			}
		}
		// usuniecie danych z pliku wymiany
		exchangeFile.deleteData(procName);
	}

	// wypisanie procesow bedacych w pamieci
	void writeProcessesNamesInRam() {
		for (int i = 0; i <pageTables.size(); i++)
			std::cout << pageTables[i].processName;
	}

	void showFIFO()
	{
		if (FIFO.size() > 0)
		{
			for (int i = 0; i < 16; i++)
			{
				std::cout << FIFO.front() << " ";
				FIFO.push(FIFO.front());
				FIFO.pop();
			}
		};
		std::cout << std::endl;
	}

	void memoryContent() //coutowaæ wszystko
	{
		std::string pom;
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				if (ram[i * 16 + j] == '\n')
				{
					pom += " ";
				}
				else pom += ram[i * 16 + j];
			}

			std::cout << "RAM[" << i * 16 << "-" << i * 16 + 15 << "]:" << pom << " ";
			pom = "";
			std::cout << "  bit odniesienia: " << framesTable[i].bit_odniesienia;
			std::cout << std::endl;
		}
	}
};