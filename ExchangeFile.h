#include <iostream>
#include <string>
#include <fstream>
#include "PageTable.h"
#include <vector>
#include <array>

struct pom
{
	std::string procName;
	const char *data = new char[16];
};

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
class ExchangeFile {
public:
	std::vector<pom> exchangeFile;
	std::vector<std::string> pomoc;


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
		int ilosc_stron = ile_potrzeba_ramek2(pomoc.size() / 16); //do poprawy na ile_potrzeba_ramek
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

		// ???? JESZCZE OBS£UGA B£ÊDU ????
	}

	void saveTo(std::string &processName, char data[16], int pageIndex)
	{ //zapisywanie ca³ej strony

		exchangeFile[pageIndex].data = data;

		// ???? JESZCZE OBS£UGA B£ÊDU ????
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