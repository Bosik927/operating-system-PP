#pragma once
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <fstream>

//exchangeFile

struct pom
{
	std::string procName;
	const char *data = new char[16];
};

class ExchangeFile {
public:
	std::vector<pom> exchangeFile;
	std::vector<std::string> pomoc;
	int ile_potrzeba_ramek2(int ile) //zwraca liczb� wymaganych ramek/stronnic wymaganych do przechowania zadanej ilo�ci znak�w
	{
		if (ile <= 0)
		{
			return 0;
		}
		int ilo��_ramek = ile / 16;
		if (ile % 16 != 0)
		{
			ilo��_ramek++;
		}

		return ilo��_ramek;
	}

	int writeTo(std::string &processName, std::string &fileName)
	{
		int licznikRozkazow = 0;
		std::ifstream program;
		program.open(fileName);
		std::string wiersz;
		while (std::getline(program, wiersz))
		{
			pomoc.push_back(wiersz);
			licznikRozkazow++;
		}
		while (pomoc.size() % 16 != 0)
		{
			pomoc.push_back(" ");
		}
		int ilosc_stron = ile_potrzeba_ramek2(pomoc.size()/16); //do poprawy na ile_potrzeba_ramek
		pom nowa;
		for (int i = 0; i < ilosc_stron; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				nowa.procName = processName;
				nowa.data = pomoc[j].c_str();
				exchangeFile.push_back(nowa);
			}
		}
		return licznikRozkazow;
	}

	const char *readFrom(std::string &processName, int pageIndex, int indexInPage)
	{
		return exchangeFile[pageIndex].data;

		// ???? JESZCZE OBS�UGA B��DU ????
	}

	void saveTo(std::string &processName, char data[16], int pageIndex)
	{ //zapisywanie ca�ej strony

		exchangeFile[pageIndex].data = data;

		// ???? JESZCZE OBS�UGA B��DU ????
	}

	void showContent()
	{
		std::cout << "Zawartosc pliku wymiany: ";
		for (pom i : exchangeFile)
		{
			std::cout << i.data << std::endl;
		}
	}

	void deleteData(std::string &processName, int howManyPages, int pageIndex)
	{
		std::cout << "Usuwanie z pliku wymiany: " << howManyPages << " stron procesu: " << processName;
		if (exchangeFile[pageIndex].procName == processName)
		{
			exchangeFile.erase(exchangeFile.begin() + pageIndex, exchangeFile.begin() + pageIndex + howManyPages);
		}
	}
};

//exchangeFile

//pageTable

class PageTable
{
public:
	int* framesNumber; //w jakich ramkach jest dana strona programu
	bool* inRAM; // czy jest w ramie
	std::string processName; //nr procesu, kt�ry jest w RAMie
	int sizeOfTable;

	PageTable(int processDataSize, std::string procName) // ???? Potrzebuj� pobra� sk�d� rozmiar procesu ????
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

	//zwraca pozycj� stronicy w RAMie lub -1, gdy stronicy nie ma w RAMie
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
	std::vector<Ramka> framesTable;;
	std::string *processNameInFrame = new std::string[16]; //NO NIBY SPOKO ZMIENNA, ALE POWINIENEM TO CHYBA POBIERA� OD ADAMA
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
				ram[i * j] = ' ';
			freeFrames.push(i);

		}
		inicjalizacja_tabeli_ramek();
	}
	void inicjalizacja_tabeli_ramek() //inicjalizuje liste ramek aby zawiera�a odpowiednie wskazania na komorki pamieci
	{
		for (int i = 0; i < 16; i++)
		{
			Ramka ramka;
			ramka.adres_poczatkowy = i * 16;
			ramka.adres_koncowy = i * 16 + 16 - 1;
			ramka.nr_ramki = i;
			framesTable.push_back(ramka);
		}
	}

	char *odczytaj_ramk�(int ramka) //odczytuje ramk� o zadanym numerze i zwraca jej zawarto�� w stringu
	{
		char *bufor = new char[16]; //tworz� bufor na odczytane dane

		for (int i = 0; i < 16; i++)
		{
			bufor[i] = ram[ramka * 16 + i]; //odczytuj� ca�� ramk�
		}
		return bufor; //zwracam stringa
	}

	void zapisz_ramk�(int numer_ramki, std::string znaki) //zapisuje znaki w konkretnej ramce (odpowiadaj�cej dostarczonemu segmentowi); nie zmienia bitu u�ywania na true; jest to zmieniane przy wyszukiwaniu wolnej ramki
	{
		int adres = numer_ramki * 16;

		for (int i = 0; i < znaki.size(); i++)
		{
			ram[adres + i] = znaki[i];
		}
	}


	//przydzielanie pami�ci

	int ramka_ze_stosu()
	{
		int ramka = freeFrames.top();
		freeFrames.pop();
		framesTable[ramka].bit_odniesienia = true;
		return ramka;
	}

	void zwolnij_ramk�(int ramka)
	{
		freeFrames.push(ramka); //oznaczam ramk� jako woln�
								//z kolejki FIFO musz� teraz usun�� t� ramk�:
		for (int i = 0; i < pageTables.size(); i++)
		{
			if (pageTables[i].processName == processNameInFrame[ramka])
				if (framesTable[ramka].bit_modyfikacji == 1) exchangeFile.saveTo(processNameInFrame[ramka], odczytaj_ramk�(ramka), pageTables[i].getIndex(ramka));
		}// tutaj do poprawienia nadpisywanie pliku wymiany
		std::queue<int> bufor; //tworz� tymczasow� kolejk� pomocnicz�
		framesTable[ramka].bit_modyfikacji = 0;
		framesTable[ramka].bit_odniesienia = 0;
		while (FIFO.size() > 0)
		{
			if (FIFO.front() != ramka)
				bufor.push(FIFO.front());
			FIFO.pop();
		}
		// odwracam kolejk�
		while (FIFO.size() > 0)
		{
			FIFO.push(bufor.front());
			bufor.pop();
		}
	}

	int ktora_ramke_zwolnic()
	{
		int pierwsza_ramka = FIFO.front();
		if (framesTable[pierwsza_ramka].bit_modyfikacji == 0 && framesTable[pierwsza_ramka].bit_odniesienia == 0)
			return pierwsza_ramka;
		else
		{
			framesTable[pierwsza_ramka].bit_odniesienia = 0;
			FIFO.push(pierwsza_ramka);
			FIFO.pop();
			while (FIFO.front() != pierwsza_ramka)
			{
				if (framesTable[FIFO.front()].bit_odniesienia == 0 && framesTable[FIFO.front()].bit_modyfikacji == 0) return FIFO.front();
				else
				{
					framesTable[FIFO.front()].bit_odniesienia = 0;
					FIFO.push(FIFO.front());
					FIFO.pop();
				}
			}
			while (FIFO.front() != pierwsza_ramka)
			{
				if (framesTable[FIFO.front()].bit_odniesienia == 0) return FIFO.front();
				else
				{
					framesTable[FIFO.front()].bit_odniesienia = 0;
					FIFO.push(FIFO.front());
					FIFO.pop();
				}
			}
		}
	}

	void writeToRam(int index, const char content[16]) {
		for (int i = 0; i < 16; i++) {
			ram[index * 16 + i] = content[i];
		}
	}

	void strona_w_ramke(int nrStrony, std::string procName)
	{
		if (freeFrames.size() <= 0) zwolnij_ramk�(ktora_ramke_zwolnic());
		for (int i = 0; i < pageTables.size(); i++)
		{
			if (pageTables[i].processName == procName)
			{
				pageTables[i].framesNumber[nrStrony] = freeFrames.top();
				pageTables[i].inRAM[nrStrony] = true;
				freeFrames.pop();
				writeToRam(pageTables[i].framesNumber[nrStrony], exchangeFile.readFrom(procName, nrStrony, 0));
			}
		}
	}

	std::string getCommand(int programCounter, std::string &processName)
	{
		PageTable *ktora_tablica;
		int pageIndex;
		if ((programCounter + 1) % 16 == 0) pageIndex = ((programCounter + 1) / 16) - 1;
		else pageIndex = ((programCounter + 1) / 16);
		for (auto &a : pageTables)
		{
			if (processName == a.processName) ktora_tablica = &a;
		}
		if (ktora_tablica->inRAM[pageIndex])
		{
			return odczytaj_ramk�(ktora_tablica->getPositionInRam(pageIndex));
		}

		else strona_w_ramke(pageIndex, ktora_tablica->processName);
		return odczytaj_ramk�(ktora_tablica->getPositionInRam(pageIndex));
	}

	// usuwanie danego procesu z pamieci
	void deleteProcessData(std::string procName) {

		// usuniecie danych z pamieci ram
		// ??? Do poprawienia
		for (int i = 0; i < 16; i++) {
			if (processNameInFrame[i] == (procName)) {
				FIFO.push(i);
				for (int j = 0; j < pageTables.size(); j++) {
					if (pageTables[j].processName == (procName))
						pageTables.erase(pageTables.begin() + j);
				}

				for (int j = 0; j < 16; j++)
					ram[i * 16 + j] = ' ';
			}
		}

		// usuniecie danych z pliku wymiany
		/*exchangeFile.deleteData(processName, int ilosc_stron, int indexstrony);*/
	}

	// wypisanie procesow bedacych w pamieci
	void writeProcessesNamesInRam() {
		for (int i = 0; i <pageTables.size(); i++)
			std::cout << pageTables[i].processName;
	}

	void memoryContent(int adres, int rozmiar) //coutowa� wszystko
	{
		for (adres; adres < adres + rozmiar; adres++)
		{
			std::cout << "RAM[" << adres << "]: " << ram[adres];
		}
	}
};