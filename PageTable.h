#pragma once
#include <iostream>
#include <string>
class PageTable
{
public:
	int* framesNumber; //w jakich ramkach jest dana strona programu
	bool* inRAM; // czy jest w ramie
	std::string processName; //nr procesu, który jest w RAMie
	int sizeOfTable;

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
		if (inRAM[pageNumber] == false)
			return -1;
		else
			return framesNumber[pageNumber];
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
			std::cout << (framesNumber[i] + " " + inRAM[i]); // ???? Pewnie do poprawy ????
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

struct Strona
{
public:
	int numer; //na jak¹ ramkê/stronê wskazuje
	bool poprawnoœæ; // 1-fizyczna 0 -wirtualna
};