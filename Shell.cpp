#include "Shell.h"

//skrypty!!!!!


Polecenia Shell::convert(const std::string &str) {
	if (str == "go" | str == "GO") return Polecenia::go; //chójoza spróbój zamieniæ 
	else if (str == "cp" | str == "CP") return Polecenia::cp;
	else if (str == "dp" | str == "DP") return Polecenia::dp;
	else if (str == "sp" | str == "SP") return Polecenia::sp;
	else if (str == "mc" | str == "MC") return Polecenia::mc;
	else if (str == "ls" | str == "LS") return Polecenia::ls;
	else if (str == "cf" | str == "CF") return Polecenia::cf;
	else if (str == "wf" | str == "WF") return Polecenia::wf;
	else if (str == "df" | str == "DF") return Polecenia::df;
	else if (str == "rf" | str == "RF") return Polecenia::rf;
	else if (str == "ref" | str == "REF") return Polecenia::reff;
	else if (str == "apf" | str == "APF") return Polecenia::apf;
	else if (str == "exit" | str == "EXIT") return Polecenia::EXIT;
	else if (str == "help" | str == "HELP") return Polecenia::HELP;
	else return Polecenia::BLAD;
}
bool Shell::is_number(const std::string &s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}
std::string Shell::text_to_string()
{
	std::string buffer;
	std::string wynik;
	while (true)
	{
		std::getline(std::cin, buffer);
		wynik += buffer;
		if (buffer[buffer.size() - 1] == 4)
		{
			break;
		}
	}
	wynik.pop_back();
	return wynik;
}

void Shell::shell()
{

	bool a = true;
	while (a)
	{
		try
		{
			std::cout << "bambosz@host: ~ $ ";
			std::string wczytywany_string;
			std::getline(std::cin, wczytywany_string);
			std::istringstream iss(wczytywany_string);
			std::vector<std::string> pom;
			do
			{
				std::string pom1;
				iss >> pom1;
				pom.push_back(pom1);
			} while (iss);
			Polecenia k = convert(pom[0]);



			switch (k)
			{
			case go:
				if (pom.size() - 1 == 1)
				{

					PCB aaa("asasa",12);
					interpreter.run(&aaa);
					std::cout << "Poszlo go" << std::endl;
				}
				else
				{
					throw 1; //tesz chójoza
				}
				break;
			case cp:
				if (pom.size() - 1 == 4)
				{
					if (is_number(pom[3])) {
						int pomoc;
						std::istringstream ss(pom[3]);
						ss >> pomoc;
						if (pomoc <= 14 && pomoc >= 0) {
							//create process
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
			case dp:
				if (pom.size() - 1 == 2) {
					std::cout << "Poszlo dp" << std::endl;
				}
				else
				{
					throw 2;
				}
				break;
			case sp:
				if (pom.size() - 1 == 2) {
					std::cout << "Poszlo sp" << std::endl;
				}
				else
				{
					throw 2;
				}
				break;
			case mc:
				if (pom.size() - 1 == 3)
				{
					if (is_number(pom[1]) && is_number(pom[2]))
					{
						int pomoc;
						std::istringstream ss(pom[1]); //to gówno zmieñ
						ss >> pomoc;
						std::cout << pomoc << std::endl;
						int pomoc1;
						std::istringstream ss1(pom[2]);
						ss1 >> pomoc1;
						std::cout << pomoc1 << std::endl;
						std::cout << "Poszlo mc" << std::endl;
					}
					else
					{
						throw 4;
					}
				}
				else
				{
					throw 2;
				}
				break;
			case ls:
				if (pom.size() - 1 == 1)
				{
					disc.wyswietlaPliki();
				}
				else
				{
					throw 1;
				}
				break;
			case cf:
				if (pom.size() - 1 == 2) {

					disc.tworzeniaPliku(pom[1]);
				}
				else
				{
					throw 2;
				}
				break;
			case wf:
			{
				if (pom.size() - 1 == 2) 
				{
					/*std::string sprawdzam;
					sprawdzam = text_to_string()*/;
					disc.wpisywanieDoPliku(pom[1], text_to_string());
				}
				else
				{
					throw 2;
				}
				
				break;
			}
			case df:
				if (pom.size() - 1 == 2) {

					disc.usuwaniePliku(pom[1]);
				}
				else
				{
					throw 2;
				}
				break;
			case rf:
				if (pom.size() - 1 == 2) {
					disc.drukujDysk(pom[1]);
				}
				else
				{
					throw 2;
				}
				break;
			case reff:
				if (pom.size() - 1 == 3)
				{
					disc.zmianaNazwy(pom[1], pom[2]);
				}
				else
				{
					throw 2;
				}
				break;
			case apf:
			{

				disc.dopiszDoPliku(pom[1], text_to_string());
			}

			break;
			case EXIT:
				if (pom.size() - 1 == 1)
				{
					a = false;
					std::cout << "Poszlo exit" << std::endl;
				}
				else
				{
					throw 1;
				}
				break;
			case HELP:
				if (pom.size() - 1 == 1)
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



					std::cout << "Poszlo help" << std::endl;
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

		}
	}
	std::getchar();//to wywal
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

