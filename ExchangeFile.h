#include <iostream>
#include <string>
#include <fstream>
#include "PageTable.h"
#include <vector>

using namespace std;

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
	std::vector<string> exchangeFile;
	const char * tab;

	int writeTo(std::string &processName, std::string &fileName)
	{

		int pageIndex = 0;
		int licznikRozkazow = 0;
		std::ifstream program;
		program.open(fileName);
		std::string wiersz;
		while (std::getline(program, wiersz))
		{
			exchangeFile.push_back(wiersz);
			licznikRozkazow++;
			pageIndex++;
		}
		while (exchangeFile.size() % 16 != 0)
		{
			exchangeFile.push_back(" ");
		}
		int ilosc_stron = ile_potrzeba_ramek(exchangeFile.size());
		return licznikRozkazow;
	}

	std::string readFrom(std::string &processName, int pageIndex, int indexInPage) {
			int a = pageIndex * 16 + pageIndex;
			return exchangeFile[a];

			// ???? JESZCZE OBS�UGA B��DU ????
		}

	void saveTo(std::string &processName, std::string &data, int pageIndex) { //zapisywanie ca�ej strony

		if (data.size() == 16) // ???? ustaw rozmiar na 16 bajt�w
		{
			int a = pageIndex * 16;
			exchangeFile.erase(exchangeFile.begin() + a, exchangeFile.begin() + a + 16);
			exchangeFile.insert(exchangeFile.begin() + a, data);
		} 
		else std::cout << ("Niepoprawny rozmiar danych, opracja zapisu danych do pliku wymiany nieudana ");

		// ???? JESZCZE OBS�UGA B��DU ????
	}

	void showContent() {
		std::cout << "Zawartosc pliku wymiany: ";
		for (std::string i : exchangeFile)
		{
			std::cout << i;
		}
	}

	void deleteData(std::string &processName, int howManyPages, int pageIndex) {
		std::cout << "Usuwanie z pliku wymiany: " << howManyPages << " stron procesu: " << processName;
		int a = pageIndex * 16;
		exchangeFile.erase(exchangeFile.begin() + a, exchangeFile.begin() + a + (howManyPages * 16));
	}
};