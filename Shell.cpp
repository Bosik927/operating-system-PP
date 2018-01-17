#include "Shell.h"





Polecenia Shell::convert(const std::string &str) {
	if (str == "go" | str == "GO") return Polecenia::go;
	else if (str == "run" | str == "RUN") return Polecenia::run;
	else if (str == "cp" | str == "CP") return Polecenia::cp;
	else if (str == "dp" | str == "DP") return Polecenia::dp;
	else if (str == "mc" | str == "MC") return Polecenia::mc;
	else if (str == "ef" | str == "EF") return Polecenia::ef;
	else if (str == "ls" | str == "LS") return Polecenia::ls;
	else if (str == "cf" | str == "CF") return Polecenia::cf;
	else if (str == "wf" | str == "WF") return Polecenia::wf;
	else if (str == "df" | str == "DF") return Polecenia::df;
	else if (str == "sproc" | str == "SPROC") return Polecenia::sproc;
	else if (str == "sprocn" | str == "SPROCN") return Polecenia::sprocn;
	else if (str == "sprocid" | str == "SPROCID") return Polecenia::sprocid;
	else if (str == "rf" | str == "RF") return Polecenia::rf;
	else if (str == "sz" | str == "SZ") return Polecenia::sz;
	else if (str == "ref" | str == "REF") return Polecenia::reff;
	else if (str == "apf" | str == "APF") return Polecenia::apf;
	else if (str == "exit" | str == "EXIT") return Polecenia::EXIT;
	else if (str == "format" | str == "FORMAT") return Polecenia::format;
	else if (str == "help" | str == "HELP") return Polecenia::HELP;
	else return Polecenia::BLAD;
}
bool Shell::is_number(const std::string &s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}
void Shell::odczyt_z_pliku(std::string a) {
	std::ifstream czytaj;
	czytaj.open(a, std::ios::in);
	if (czytaj.is_open() == true)
	{
		while (std::getline(czytaj, this->pom1))
		{
			this->vector_skrypt.push_back(this->pom1);
		}
		czytaj.close();
	}
	else
	{
		throw 7;
	}
}

void Shell::interpret(std::string a)
{
	this->vector_str.clear();
	std::istringstream iss(a);
	do
	{
		iss >> this->pom1;
		this->vector_str.push_back(this->pom1);

	} while (iss);

	this->k = Shell::convert(this->vector_str[0]);

	try
	{

		switch (k)
		{
		case go:
		{
			if (this->vector_str.size() - 1 == 1)
			{
				auto proces = pm.AssignProcessor();
				interpreter.run(proces);
				std::cout << "Poszlo go" << std::endl;
			}
			else
			{
				throw 1;
			}
			break;
		}
		case cp:
		{
			if (this->vector_str.size() - 1 == 4)
			{
				if (is_number(this->vector_str[3])) {
					int pomoc;
					std::istringstream ss(this->vector_str[3]);
					ss >> pomoc;
					if (pomoc <= 14 && pomoc >= 0) {
						std::cout << pm.CreateProces(this->vector_str[1], this->vector_str[2], pomoc);
					}
					else
					{
						throw 5;
					}
				}
				else
				{
					throw 3;
				}
			}
			else
			{
				std::cout << "NIE Poszlo cp" << std::endl;
				throw 2;
			}
			break;
		}
		case sproc:
		{
			if (this->vector_str.size() - 1 == 1)
			{
				std::cout << pm.DisplayAllProcesses();
			}
			else
			{
				throw 2;
			}
			break;
		}
		case sprocn:
		{
			if (this->vector_str.size() - 1 == 2)
			{
				std::cout << pm.DisplayProcessByName(this->vector_str[1]);
			}
			else
			{
				throw 2;
			}
			break;
		}
		case sprocid:
		{
			if (this->vector_str.size() - 1 == 2)
			{
				if (is_number(this->vector_str[1])) {
					int pomoc;
					std::istringstream ss(this->vector_str[1]);
					ss >> pomoc;

					std::cout << pm.DisplayProcessByID(pomoc);
				}
				else
				{
					throw 6;
				}
			}
			else
			{
				throw 2;
			}
			break;
		}
		case dp:
		{
			if (this->vector_str.size() - 1 == 2) {
				std::cout << pm.DeleteProcess(pm.getIdFromName(this->vector_str[1]));
			}
			else
			{
				throw 2;
			}
			break;
		}
		case sz:
		{
			if (this->vector_str.size() - 1 == 2) {
				disc.stan_zamka(this->vector_str[1]);
				
			}
			else
			{
				throw 2;
			}
			break;
		}
		case mc:
		{
			if (this->vector_str.size() - 1 == 1)
			{
				ram.memoryContent();
			}
			else
			{
				throw 2;
			}
			break;
		}
		case ef:
		{
			if (this->vector_str.size() - 1 == 1)
			{
				ram.exchangeFile.showContent();
			}
			else
			{
				throw 2;
			}
			break;
		}
		case ls:
		{
			if (this->vector_str.size() - 1 == 1)
			{
				disc.wyswietlaPliki();
			}
			else
			{
				throw 1;
			}
			break;
		}
		case cf:
		{
			if (this->vector_str.size() - 1 == 2) {

				disc.tworzeniaPliku(this->vector_str[1]);
			}
			else
			{
				throw 2;
			}
			break;
		}
		case wf:
		{
			if (this->vector_str.size() - 1 == 3)
			{
				disc.wpisywanieDoPliku(this->vector_str[1], this->vector_str[2]);
			}
			else
			{
				throw 2;
			}
			break;
		}
		case df:
		{
			if (this->vector_str.size() - 1 == 2) {
				disc.usuwaniePliku(this->vector_str[1]);
			}
			else
			{
				throw 2;
			}
			break;
		}
		case rf:
		{
			if (this->vector_str.size() - 1 == 2) {
				disc.drukujDysk(this->vector_str[1]);
			}
			else
			{
				throw 2;
			}
			break;
		}
		case reff:
		{
			if (this->vector_str.size() - 1 == 3)
			{
				disc.zmianaNazwy(this->vector_str[1], this->vector_str[2]);
			}
			else
			{
				throw 2;
			}
			break;
		}
		case apf:
		{
			if (this->vector_str.size() - 1 == 3)
			{
				disc.dopiszDoPliku(this->vector_str[1], this->vector_str[2]);
			}
			else
			{
				throw 2;
			}
			break;
		}
		case run:
		{
			if (this->vector_str.size() - 1 == 2)
			{
				this->vector_skrypt.clear();
				Shell::odczyt_z_pliku(this->vector_str[1]);
				for(int i=0;i<this->vector_skrypt.size();i++)
				{
					Shell::interpret(this->vector_skrypt[i]);
				}
			}
			else
			{
				throw 2;
			}
			break;
		}
		case format:
		{
			if (this->vector_str.size() - 1 == 2)
			{
				if (this->vector_str[1] == "C")
				{
					system("COLOR 01");
					
					
				}
				
			}
			else
			{
				throw 2;
			}
			break;
		}
		case EXIT:
		{
			if (this->vector_str.size() - 1 == 1)
			{
				this->a = false;
			}
			else
			{
				throw 1;
			}
			break;
		}
		case HELP:
		{
			if (this->vector_str.size() - 1 == 1)
			{
				std::cout << "GO" << std::endl;
				std::cout << "CP" << std::endl;
				std::cout << "MC" << std::endl;
				std::cout << "LS - wiew files" << std::endl;
				std::cout << "CF (name) - create file" << std::endl;
				std::cout << "WF (name) - write file" << std::endl;
				std::cout << "DF (name) - delete file" << std::endl;
				std::cout << "RF (name) - read file" << std::endl;
				std::cout << "REF (name)(newname) - rename file" << std::endl;
				std::cout << "APF (name)(data) - append file" << std::endl;
				std::cout << "EXIT" << std::endl;

			}
			else
			{
				throw 1;
			}
			break;
		default:
			std::cout << "nie ma komendy" << std::endl;
			break;
		}
		}
	}
	catch (int error_no)
	{
		if (error_no == 1)
		{
			std::cout << "Za duzo argumentow" << std::endl;
		}
		if (error_no == 2)
		{
			std::cout << "Zla ilosc argumentow" << std::endl;
		}
		if (error_no == 3)
		{
			std::cout << "rozmiar musi byc liczba" << std::endl;
		}
		if (error_no == 4)
		{
			std::cout << "adres i rozmiar musi byc liczba" << std::endl;
		}
		if (error_no == 5)
		{
			std::cout << "prioryten przyjmuje wartosc od 0 do 14" << std::endl;
		}
		if (error_no == 6)
		{
			std::cout << "id procesu musi byc liczba" << std::endl;
		}
		if (error_no == 7)
		{
			std::cout << "plik nie zostal otworzony" << std::endl;
		}
	}

}
void Shell::shell()
{
	while (this->a)
	{
		std::cout << "grazia@host: ~ $ ";
		std::getline(std::cin, wczytywany_string);
		Shell::interpret(wczytywany_string);

	}
}
void Shell::logo() {//lol
	int i = 50;
	std::cout << "         GGGGGGGGGGG          RRRRRRRRRRRRRR          AAAAAAAAAAAAAAAAA   \n";
	Sleep(i);
	std::cout << "       GGGGGGGGGGGGGGG       RRRRRRRRRRRRRRRRR       AAAAAAAAAAAAAAAAAAA  \n";
	Sleep(i);
	std::cout << "      GGGGG      GGGGGG     RRRRRR        RRRRR     AAAAAA         AAAAAA \n";
	Sleep(i);
	std::cout << "      GGGGG       GGGGGG    RRRRR         RRRRR    AAAAAA           AAAAAA \n";
	Sleep(i);
	std::cout << "      GGGGG       GGGGGG    RRRRR         RRRRR    AAAAAA           AAAAAA \n";
	Sleep(i);
	std::cout << "      GGGGG                 RRRRRRRRRRRRRRRRR      AAAAAAA         AAAAAAA \n";
	Sleep(i);
	std::cout << "      GGGGG     GGGGG       RRRRRRRRRRRRRRR        AAAAAAAAAAAAAAAAAAAAAAA \n";
	Sleep(i);
	std::cout << "      GGGGG      GGGGGG     RRRRR      RRRRR       AAAAAAAAAAAAAAAAAAAAAAA \n";
	Sleep(i);
	std::cout << "      GGGGG       GGGGGG    RRRRR       RRRRR      AAAAAAA         AAAAAAA \n";
	Sleep(i);
	std::cout << "      GGGGG        GGGGGG   RRRRR       RRRRRR     AAAAAA           AAAAAA \n";
	Sleep(i);
	std::cout << "       GGGGGGGGGGGGGGGGG    RRRRRR      RRRRRRR    AAAAAA           AAAAAA \n";
	Sleep(i);
	std::cout << "         GGGGGGGGGGGGG      RRRRRRR     RRRRRRRR   AAAAAA           AAAAAA \n\n";
	Sleep(2 * i);
	std::cout << "      ZZZZZZZZZZZZZZZZZZZZZ    IIIIIIIIIIIII        AAAAAAAAAAAAAAAAA     \n";
	Sleep(i);
	std::cout << "      ZZZZZZZZZZZZZZZZZZZZZ    IIIIIIIIIIIII       AAAAAAAAAAAAAAAAAAA    \n";
	Sleep(i);
	std::cout << "                     ZZZZZ          III           AAAAAA         AAAAAA   \n";
	Sleep(i);
	std::cout << "                    ZZZZZ           III          AAAAAA           AAAAAA  \n";
	Sleep(i);
	std::cout << "                  ZZZZZ             III          AAAAAA           AAAAAA           OOOOOOOOO            SSSSSS \n";
	Sleep(i);
	std::cout << "               ZZZZZZ               III          AAAAAAA         AAAAAAA         OOOOOOOOOOOOO       SSSSSSS    \n";
	Sleep(i);
	std::cout << "            ZZZZZ                   III          AAAAAAAAAAAAAAAAAAAAAAA        OOOOO     OOOOO     SSSSSS          \n";
	Sleep(i);
	std::cout << "          ZZZZZ                     III          AAAAAAAAAAAAAAAAAAAAAAA        OOOO       OOOO    SSSSSS \n";
	Sleep(i);
	std::cout << "        ZZZZZ                       III          AAAAAAA         AAAAAAA        0000       OOOO       SSSSSSSS \n";
	Sleep(i);
	std::cout << "       ZZZZZ                        III          AAAAAA           AAAAAA         OOOO     OOOO         SSSSSS  \n";
	Sleep(i);
	std::cout << "      ZZZZZZZZZZZZZZZZZZZZ     IIIIIIIIIIIII     AAAAAA           AAAAAA          OOOOOOOOOOOO      SSSSSSS  \n";
	Sleep(i);
	std::cout << "      ZZZZZZZZZZZZZZZZZZZZ     IIIIIIIIIIIII     AAAAAA           AAAAAA      0     OOOOOOOO     SSSSSSS        \n";
	Sleep(1000);
	system("cls");
}

