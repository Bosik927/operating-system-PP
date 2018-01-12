#include <iostream>
#include <string>
#include <fstream>
#include "PageTable.h"
#include <vector>
#include <array>

using namespace std;

struct pom
{
	std::string procName;
	char *data = new char[16];
};

int ile_potrzeba_ramek(int ile) //zwraca liczb� wymaganych ramek/stronnic wymaganych do przechowania zadanej ilo�ci znak�w
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
class ExchangeFile {
public:
	std::fstream exchange;
	std::string fileName = "exchangefile.txt";
	std::vector<pom> exchangeFile;
	std::vector<string> pomoc;


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
		while (exchangeFile.size() % 16 != 0)
		{
				pomoc.push_back(" ");
		}
		int ilosc_stron = ile_potrzeba_ramek(exchangeFile.size());
		pom nowa;
		for (int i = 0; i < ilosc_stron; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				nowa.procName = processName;
				nowa.data += wiersz[i];
				exchangeFile.push_back(nowa);
			}
		}
		return licznikRozkazow;
	}

	char readFrom(std::string &processName, int pageIndex, int indexInPage) 
	{
			return exchangeFile[pageIndex].data[indexInPage];

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
			std::cout << i.data;
		}
	}

	void deleteData(std::string &processName, int howManyPages, int pageIndex)
	{
		std::cout << "Usuwanie z pliku wymiany: " << howManyPages << " stron procesu: " << processName;
		while (exchangeFile[pageIndex].procName == processName)
		{
			exchangeFile.erase(exchangeFile.begin() + pageIndex, exchangeFile.begin() + pageIndex + howManyPages);
		}
	}
};