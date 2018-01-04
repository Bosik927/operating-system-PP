#pragma once
#include <iostream>
#include <string>
#include <list>
#include "PageTable.h"
#include <queue>
#include "ExchangeFile.h"
#include <stack>
class RAM
{
private:
public:

	char *ram = new char[256];
	Ramka *framesTable = new Ramka;
	std::string *processNameInFrame = new std::string[16]; //NO NIBY SPOKO ZMIENNA, ALE POWINIENEM TO CHYBA POBIERAÆ OD ADAMA
	std::queue<int> FIFO;
	ExchangeFile exchangeFile;
	//tabela stron
	std::vector<PageTable> pageTables;
	std::stack<int> freeFrames;

	// konstruktor, ustawienie podstawowych parametrow
	RAM() {
		for (int i = 0; i < 16; i++) {
			processNameInFrame[i] = "";
			for (int j = 0; j < 16; j++)
				ram[i * j] = ' ';
			freeFrames.push(i);
			inicjalizacja_tabeli_ramek();
		}
	}

	//operacje na ramkach

	void inicjalizacja_tabeli_ramek() //inicjalizuje liste ramek aby zawiera³a odpowiednie wskazania na komorki pamieci
	{
		for (int i = 0; i < 16; i++)
		{
			Ramka ramka;
			ramka.adres_poczatkowy = i * 16;
			ramka.adres_koncowy = i * 16 + 16 - 1;
			ramka.nr_ramki = i;
			framesTable[i] = ramka;
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

	void zapisz_ramkê(int numer_ramki, string znaki) //zapisuje znaki w konkretnej ramce (odpowiadaj¹cej dostarczonemu segmentowi); nie zmienia bitu u¿ywania na true; jest to zmieniane przy wyszukiwaniu wolnej ramki
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

		if (framesTable[ramka].bit_modyfikacji == 1) exchangeFile.saveTo(processNameInFrame[ramka], odczytaj_ramkê(ramka), pageTables[].getIndex); // tutaj do poprawienia nadpisywanie pliku wymiany
		std::queue<int> bufor; //tworzê tymczasow¹ kolejkê pomocnicz¹
		framesTable[ramka].bit_modyfikacji = 0;
		framesTable[ramka].bit_odniesienia = 0;
		while (FIFO.size() > 0)
		{
			if (FIFO.front() != ramka)
				bufor.push(FIFO.front());
			FIFO.pop();
		}
		// odwracam kolejkê
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

	void writeToRam(int index, char content[16]) {
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
					pageTables[i].framesNumber[nrStrony] = freeFrames.top();
					pageTables[i].inRAM[nrStrony] = true;
					freeFrames.pop();
					writeToRam(pageTables[i].framesNumber[nrStrony], exchangeFile.readFrom(procName, nrStrony, 0));
				}
			}
	}

	std::string getCommand(int programCounter, std::string processName, PageTable pt)
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
			return odczytaj_ramkê(ktora_tablica->getPositionInRam);
		}

		else strona_w_ramke(pageIndex, ktora_tablica->processName);
	}

	// usuwanie danego procesu z pamieci
	void deleteProcessData(std::string processName) {

		// usuniecie danych z pamieci ram
		// ??? Do poprawienia
		for (int i = 0; i < 16; i++) {
			if (processNameInFrame[i] == (processName)) {
				FIFO.push(i);
				for (int j = 0; j < pageTables.size(); j++) {
					if (pageTables[j].processName == (processName))
						pageTables.erase[j];
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

	void memoryContent(int adres, int rozmiar) //coutowaæ wszystko
	{
		for (adres; adres < adres + rozmiar; adres++)
		{
			std::cout << ram[adres];
		}
	}

};