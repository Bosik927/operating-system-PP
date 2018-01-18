#include "plikiFAT.h"

Disc::Disc()
{

	for (int i = 0; i < 64; i++) {
		Tab_Fat pom;
		atrybuty[i] = pom;;
	}
	atrybuty[0].status = false;
	for (int i = 0; i<rozmiarDysku; i++)
	{
		dysk[i] = 0;							//zerwoanie dysku;
	}

	for (int i = 0; i<64; i++)
	{
		fat[i] = 0;
		atrybuty[i].status = false;
		atrybuty[i].zapisany = false;
	}
}

std::string Disc::zawartoscDisc()
{
	return "Rozmiar dysku: " + std::to_string(this->rozmiarDysku) + " wolne miejsce: " + std::to_string(this->wolneMiejsceDysk());
}
std::string Disc::zawartoscPlik(std::string nazwa)
{
	for (int i = 0; i < 64; i++)
	{
		if (atrybuty[i].nazwa == (nazwa))
		{
			return "Nazwa: " + atrybuty[i].nazwa + " status: " + std::to_string(atrybuty[i].status) + " czy zapisany: " + std::to_string(atrybuty[i].zapisany) + " pierwszy jap: " + std::to_string(atrybuty[i].jap1) + " rozmiar: " + std::to_string(atrybuty[i].rozmiar);
		}
	}
}
void Disc::otworzPlik(std::string nazwa, PCB* process)
{
	for (int i = 0; i < 64; i++)
	{
		if (atrybuty[i].nazwa == nazwa )
		{
			atrybuty[i].zamek.lock(*process);
		}
	}
}
void Disc::zamknijPlik(std::string nazwa, PCB* process)
{
	for (int i = 0; i < 64; i++)
	{
		if (atrybuty[i].nazwa == nazwa )
		{
			atrybuty[i].zamek.unlock(*process);
		}
	}
}

//void Disc::tworzeniaPliku(std::string nazwa, PCB* process)		//parametry nazwa rozszerzenie
//{
//	
//
//	int buffor; 		// zmienne pomocnicze
//	int buffor1;
//
//	if (nazwaIstnieje(nazwa) == true)
//	{
//		buffor = szukanieWolnegoJap();
//		buffor1 = wolnyKatalog();
//
//		atrybuty[buffor1].zamek.lock(*process);
//
//		//uzupelnienie wpisow do katalogu
//		atrybuty[buffor1].nazwa = nazwa;
//		atrybuty[buffor1].status = true;
//		atrybuty[buffor1].jap1 = buffor;
//		atrybuty[buffor1].rozmiar = 0;
//		atrybuty[buffor1].zapisany = false;
//		fat[buffor] = -1;
//
//		std::cout << "Plik zostal utworzony!" << std::endl;
//		//	iloscWolnegoMiejsca();
//		atrybuty[buffor1].zamek.unlock(*process);
//
//	}
//	else if (wolnyKatalog() == -1)// sprawdz czy w fat
//	{
//		std::cout << "Katalog jest pelny" << std::endl;
//	}
//	else if (wolneMiejsceDysk() <64)
//	{
//		std::cout << "Dysk jest pelny" << std::endl;
//
//	}
//	else
//		std::cout << "Istnieje juz plik o takiej nazwie" << std::endl;
//
//}
void Disc::tworzeniaPliku(std::string nazwa)		//parametry nazwa rozszerzenie
{


	int buffor; 		// zmienne pomocnicze
	int buffor1;

	if (nazwaIstnieje(nazwa) == true)
	{
		buffor = szukanieWolnegoJap();
		buffor1 = wolnyKatalog();


		//uzupelnienie wpisow do katalogu
		atrybuty[buffor1].nazwa = nazwa;
		atrybuty[buffor1].status = true;
		atrybuty[buffor1].jap1 = buffor;
		atrybuty[buffor1].rozmiar = 0;
		atrybuty[buffor1].zapisany = false;
		fat[buffor] = -1;

		std::cout << "Plik zosta³ utworzony!" << std::endl;
		//	iloscWolnegoMiejsca();

	}
	else if (wolnyKatalog() == -1)// sprawdz czy w fat
	{
		std::cout << "Katalog jest pelny" << std::endl;
	}
	else if (wolneMiejsceDysk() <64)
	{
		std::cout << "Dysk jest pelny" << std::endl;

	}
	else
		std::cout << "Istnieje juz plik o takiej nazwie" << std::endl;

}

int Disc::file_jap(std::string nazwa)
{

	for (int i = 0; i < 64; i++) {
		if (atrybuty[i].nazwa == nazwa)
			return atrybuty[i].jap1;
	}
	return -1;
}
void Disc::wys()
{
	for (int i = 0; i<64; i++)
	{
		std::cout << ("Numer: ");
		std::cout << (i);
		std::cout << (" \t");
		std::cout << ("Fat: ");
		if (fat[i] != 0)
		{
			if (fat[i] == -1) {
				std::cout << ("zajety");
			}
			else
				std::cout << (fat[i]);
		}
		else
			std::cout << (fat[i]);

	}
}
void Disc::wpisywanieDoPliku(std::string nazwa, std::string data)
{

	int jap1;
	int nastepnyJap;
	double dlugosc;
	double count_jap = 0;

	dlugosc = data.length();
	count_jap = ceil(dlugosc / 64);
	//std::cout<<("DLUGOSC JAP "+count_jap);
	// Czy katalog wolny?  
	if (ktory_katalog(nazwa) != -1) {
		if (atrybuty[ktory_katalog(nazwa)].zapisany == false)
			atrybuty[ktory_katalog(nazwa)].zapisany = true;

		if (file_jap(nazwa) != -1) {
			if ((spacefree) > dlugosc) {
				jap1 = file_jap(nazwa);

				//DLA PIERWSZEGO 
				//std::cout<<("pocz¹tek pliku "+jap1);
				char * datachar = new char[data.size() + 1];
				strcpy(datachar, data.c_str());

				for (int q = 0; q < data.length() && q < 64; q++) {
					//if (k <= dlugosc - 1) {
					dysk[q + jap1 * 64] = datachar[q];
					//std::cout<<(q+jap1*64+" -> "+dysk[q+jap1*64]);

				}
				//DLA WIECEJ
				if (count_jap > 1) {
					for (int j = 1; j <= count_jap - 1; j++) {
						nastepnyJap = szukanieWolnegoJap();
						//std::cout<<("WOLNY NEXT JAP "+nastepnyJap);
						fat[nastepnyJap] = -1;
						fat[jap1] = nastepnyJap;
						jap1 = nastepnyJap;
						for (int q = 0; q < 64 && q < data.length() - j * 64; q++) {
							dysk[q + jap1 * 64] = datachar[q + j * 64];
							//	std::cout<<(q+jap1*64+" -> "+dysk[q+jap1*64]);
						}

					}
				}
				std::cout << "Wpisanie do pliku pomyslne" << std::endl;
				atrybuty[ktory_katalog(nazwa)].rozmiar = data.length();

			}
			else std::cout << "Za malo miejsca na dysku" << std::endl;
		}
		else  std::cout << "Nie mozna nadpisac danych" << std::endl;
	}
	else std::cout << "Blad! Plik nie istnieje" << std::endl;
	iloscWolnegoMiejsca();



}

void Disc::wpisywanieDoPliku(std::string nazwa, std::string data, PCB* process)
{

	int jap1;
	int nastepnyJap;
	double dlugosc;
	double count_jap = 0;

	dlugosc = data.length();
	count_jap = ceil(dlugosc / 64);
	//std::cout<<("DLUGOSC JAP "+count_jap);
	// Czy katalog wolny?  

	if (ktory_katalog(nazwa) != -1) {
		if (atrybuty[ktory_katalog(nazwa)].zapisany == false)
			if (atrybuty[ktory_katalog(nazwa)].zamek.lock(*process))
			{
				atrybuty[ktory_katalog(nazwa)].zapisany = true;
				if (file_jap(nazwa) != -1) {
					if ((spacefree) > dlugosc) {
						jap1 = file_jap(nazwa);

						//DLA PIERWSZEGO 
						//std::cout<<("pocz¹tek pliku "+jap1);
						char * datachar = new char[data.size() + 1];
						strcpy(datachar, data.c_str());

						for (int q = 0; q < data.length() && q < 64; q++) {
							//if (k <= dlugosc - 1) {
							dysk[q + jap1 * 64] = datachar[q];
							//std::cout<<(q+jap1*64+" -> "+dysk[q+jap1*64]);

						}
						//DLA WIECEJ
						if (count_jap > 1) {
							for (int j = 1; j <= count_jap - 1; j++) {
								nastepnyJap = szukanieWolnegoJap();
								//std::cout<<("WOLNY NEXT JAP "+nastepnyJap);
								fat[nastepnyJap] = -1;
								fat[jap1] = nastepnyJap;
								jap1 = nastepnyJap;
								for (int q = 0; q < 64 && q < data.length() - j * 64; q++) {
									dysk[q + jap1 * 64] = datachar[q + j * 64];
									//	std::cout<<(q+jap1*64+" -> "+dysk[q+jap1*64]);
								}

							}
						}
						std::cout << "Wpisanie do pliku pomyslne" << std::endl;
						atrybuty[ktory_katalog(nazwa)].rozmiar = data.length();
					//	atrybuty[ktory_katalog(nazwa)].zamek.unlock(*process);
					}
					else std::cout << "Za malo miejsca na dysku" << std::endl;
				}
				else  std::cout << "Nie mozna nadpisac danych" << std::endl;
			}
	}
	else std::cout << "Blad! Plik nie istnieje" << std::endl;
	iloscWolnegoMiejsca();



}

int Disc::wolneMiejsceDysk()
{
	int count = 0;
	for (int i = 0; i< rozmiarDysku; i++)
	{
		if ((int)dysk[i] == 0)
		{
			count++;
		}
		else
		{
			count = 0;
		}
	}
	return count;
}
void Disc::usuwaniePliku(std::string nazwa)
{
	int jap = file_jap(nazwa);
	int kolejnyJap;
	int buffor = 1;
	int tab[64];
	tab[0] = jap;
	while (jap != -1)
	{
		kolejnyJap = fat[jap];
		jap = kolejnyJap;
		tab[buffor] = kolejnyJap;
		buffor++;
	}
	buffor -= 1;

	if (nazwaIstnieje(nazwa) == false)
	{

		for (int i = 0; i < buffor; i++)
		{
			for (int j = 0; j < 64; j++)
			{
				dysk[(tab[i] * 64) + j] = 0;
			}
			fat[tab[i]] = 0;
		}
		int x = ktory_katalog(nazwa);
		if (atrybuty[x].nazwa == (nazwa))
		{
			atrybuty[x].nazwa = "";
			atrybuty[x].rozmiar = 0;
			atrybuty[x].status = false;
			atrybuty[x].jap1 = 0;
			atrybuty[x].zapisany = false;
		}
		iloscWolnegoMiejsca();
		std::cout << ("Usuwanie pliku przebieglo pomyslnie") << std::endl;
	}
	else
		std::cout << ("Plik nie istnieje") << std::endl;

}

void Disc::usuwaniePliku(std::string nazwa, PCB* process)
{
	int jap = file_jap(nazwa);
	int kolejnyJap;
	int buffor = 1;
	int tab[64];
	tab[0] = jap;
	while (jap != -1)
	{
		kolejnyJap = fat[jap];
		jap = kolejnyJap;
		tab[buffor] = kolejnyJap;
		buffor++;
	}
	buffor -= 1;
	int x = ktory_katalog(nazwa);
	if (atrybuty[x].zamek.lock(*process))
	{
		if (nazwaIstnieje(nazwa) == false)
		{

			for (int i = 0; i < buffor; i++)
			{
				for (int j = 0; j < 64; j++)
				{
					dysk[(tab[i] * 64) + j] = 0;
				}
				fat[tab[i]] = 0;
			}

			if (atrybuty[x].nazwa == (nazwa))
			{
				atrybuty[x].nazwa = "";
				atrybuty[x].rozmiar = 0;
				atrybuty[x].status = false;
				atrybuty[x].jap1 = 0;
				atrybuty[x].zapisany = false;
			}
			iloscWolnegoMiejsca();
			std::cout << ("Usuwanie pliku przebieglo pomyslnie");
		}
		else
			std::cout << ("Plik nie istnieje");
	}

}


////do ogarniecia
void Disc::stan_zamka(std::string a) {
	std::cout << this->atrybuty[ktory_katalog(a)].zamek.toString() << std::endl;
}
void Disc::wyswietlaPliki()
{
	int allsize = 0;
	int l = 0;
	std::cout << "Directory of root:" << std::endl;

	std::cout << "Nazwa   Rozmiar ";
	std::cout << std::endl;
	for (int i = 0; i < 64; i++)
	{
		if (atrybuty[i].status == true)
		{
			std::cout << atrybuty[i].nazwa;
			std::cout << "     ";
			std::cout << atrybuty[i].rozmiar;
			std::cout << std::endl;
			l++;
			allsize += atrybuty[i].rozmiar;
		}
	}
	std::cout << std::endl;
	int a = rozmiarDysku - allsize;
	//std::cout << l, " plik(i)", " \t", allsize, " bajty";
	//std::cout << std::endl;
	//std::cout << "\t", "\t", "\t", "\t" + a, " wolne bajty";
}

void Disc::iloscWolnegoMiejsca()
{

	int free = 0;
	for (int i = 0; i<64; i++)
	{
		if (fat[i] == 0)
		{

			free++;
		}

	}
	spacefree = free * 64;
}

void Disc::drukujDysk(std::string nazwa)
{
	int jap = file_jap(nazwa);
	int nextJap;
	int l = 1;
	int tab[64];
	tab[0] = jap;

	if (jap != -1 && atrybuty[ktory_katalog(nazwa)].nazwa == (nazwa))
	{
		while (jap != -1)
		{
			nextJap = fat[jap];
			jap = nextJap;
			tab[l] = nextJap;
			l++;
		}
		l -= 1;
		std::cout << ("Plik o nazwie " + nazwa);
		std::cout << (" o zawartosci: ");
		for (int i = 0; i<l; i++)
		{
			int j = 64 * tab[i];

			int k = j + 64;
			for (int z = j; z<k; z++)
			{
				std::cout << (dysk[z]);
			}
		}std::cout << std::endl;
	}
	else
	{
		std::cout << ("Nie znaleziono podanego pliku") << std::endl;
	}
}

void Disc::www()
{
	for (int i = 0; i< rozmiarDysku; i++)
	{
		std::cout << ("nr" + i, " " + dysk[i], " ");
	}
}


void Disc::zmianaNazwy(std::string nazwa, std::string newname)
{
	if (nazwaIstnieje(newname) == true)
	{
		if (file_jap(nazwa) != -1)
		{
			for (int i = 0; i <64; i++)
			{
				if (atrybuty[i].nazwa == (nazwa))
				{
					atrybuty[i].nazwa = newname;
				}
			}
			std::cout << ("Zmiana nazwy przebiegla pomylnie") << std::endl;
		}
		else
		{
			std::cout << ("Nie znaleziono pliku") << std::endl;
		}
	}
	else
	{
		std::cout << ("Plik nie istnieje") << std::endl;
	}
}
void Disc::zmianaNazwy(std::string nazwa, std::string newname,PCB* process)
{
	if (nazwaIstnieje(newname) == true)
	{
		if (file_jap(nazwa) != -1)
		{
			for (int i = 0; i <64; i++)
			{
				if (atrybuty[i].nazwa == (nazwa))
				{
					if (atrybuty[i].zamek.lock(*process))
					{
						atrybuty[i].nazwa = newname;
						std::cout << ("Zmiana nazwy przebiegla pomylnie");
					}
					break;
				}
			}

		}
		else
		{
			std::cout << ("Nie znaleziono pliku");
		}
	}
	else
	{
		std::cout << ("Plik nie istnieje");
	}
}
void Disc::dopiszDoPliku(std::string nazwa, std::string data)
{
	std::string dane1 = "";
	int jap = file_jap(nazwa);
	int nextJap;
	int l = 1;
	int tab[64];
	tab[0] = jap;


	while (jap != -1)
	{
		nextJap = fat[jap];
		jap = nextJap;
		tab[l] = nextJap;
		l++;
	}
	l -= 1;

	for (int i = 0; i<l; i++)
	{
		int j = 64 * tab[i];

		int k = j + 64;
		for (int z = j; z<k; z++)
		{
			if (dysk[z] != 0)
				dane1 += dysk[z];
		}

	}
	jap = file_jap(nazwa);
	int kolejnyJap;
	int buffor = 1;
	tab[0] = jap;
	while (jap != -1)
	{
		kolejnyJap = fat[jap];
		jap = kolejnyJap;
		tab[buffor] = kolejnyJap;
		buffor++;
	}
	buffor -= 1;


	for (int i = 0; i<buffor; i++)
	{
		for (int j = 0; j < 64; j++)
		{
			dysk[(tab[i] * 64) + j] = 0;
		}
		fat[tab[i]] = 0;
	}
	int x = ktory_katalog(nazwa);
	if (atrybuty[x].nazwa == (nazwa))
	{
		atrybuty[x].nazwa = "";
		atrybuty[x].rozmiar = 0;
		atrybuty[x].status = false;
		atrybuty[x].jap1 = 0;
		atrybuty[x].zapisany = false;
	}
	iloscWolnegoMiejsca();



	int buffor1;


	buffor = szukanieWolnegoJap();
	buffor1 = wolnyKatalog();



	//uzupelnienie wpisow do katalogu
	atrybuty[buffor1].nazwa = nazwa;
	atrybuty[buffor1].status = true;
	atrybuty[buffor1].jap1 = buffor;
	atrybuty[buffor1].rozmiar = 0;
	atrybuty[buffor1].zapisany = false;
	fat[buffor] = -1;
	data = dane1 + data;
	int jap1;
	int nastepnyJap;
	double dlugosc;
	double count_jap = 0;

	dlugosc = data.length();
	count_jap = ceil(dlugosc / 64);
	//   std::cout<<("DLUGOSC JAP "+count_jap);
	// Czy katalog wolny?  
	if (ktory_katalog(nazwa) != -1) {
		if (atrybuty[ktory_katalog(nazwa)].zapisany == false)
			atrybuty[ktory_katalog(nazwa)].zapisany = true;

		if (file_jap(nazwa) != -1) {
			if ((spacefree) > dlugosc) {
				jap1 = file_jap(nazwa);

				//DLA PIERWSZEGO 
				//	std::cout<<("pocz¹tek pliku "+jap1);
				char * datachar = new char[data.size() + 1];
				strcpy(datachar, data.c_str());
				for (int q = 0; q < data.length() && q < 64; q++) {
					//if (k <= dlugosc - 1) {
					dysk[q + jap1 * 64] = datachar[q];
					//std::cout<<(q+jap1*64+" -> "+dysk[q+jap1*64]);

				}
				//DLA WIECEJ
				if (count_jap > 1) {
					for (int j = 1; j <= count_jap - 1; j++) {
						nastepnyJap = szukanieWolnegoJap();
						//std::cout<<("WOLNY NEXT JAP "+nastepnyJap);
						fat[nastepnyJap] = -1;
						fat[jap1] = nastepnyJap;
						jap1 = nastepnyJap;
						for (int q = 0; q < 64 && q < data.length() - j * 64; q++) {
							dysk[q + jap1 * 64] = datachar[q + j * 64];
							//	std::cout<<(q+jap1*64+" -> "+dysk[q+jap1*64]);
						}

					}
				}
				std::cout << ("Wpisanie do pliku pomyslne") << std::endl;
				atrybuty[ktory_katalog(nazwa)].rozmiar = data.length();

			}
			else std::cout << ("Za malo miejsca na dysku") << std::endl;
		}
		else  std::cout << ("Nie mozna nadpisac danych") << std::endl;
	}
	else std::cout << ("Blad! Plik nie istnieje") << std::endl;
	iloscWolnegoMiejsca();


}
void Disc::dopiszDoPliku(std::string nazwa, std::string data, PCB* process)
{
	std::string dane1 = "";
	int jap = file_jap(nazwa);
	int nextJap;
	int l = 1;
	int tab[64];
	tab[0] = jap;


	while (jap != -1)
	{
		nextJap = fat[jap];
		jap = nextJap;
		tab[l] = nextJap;
		l++;
	}
	l -= 1;

	for (int i = 0; i < l; i++)
	{
		int j = 64 * tab[i];

		int k = j + 64;
		for (int z = j; z < k; z++)
		{
			if (dysk[z] != 0)
				dane1 += dysk[z];
		}

	}
	jap = file_jap(nazwa);
	int kolejnyJap;
	int buffor = 1;
	tab[0] = jap;
	while (jap != -1)
	{
		kolejnyJap = fat[jap];
		jap = kolejnyJap;
		tab[buffor] = kolejnyJap;
		buffor++;
	}
	buffor -= 1;


	for (int i = 0; i < buffor; i++)
	{
		for (int j = 0; j < 64; j++)
		{
			dysk[(tab[i] * 64) + j] = 0;
		}
		fat[tab[i]] = 0;
	}
	int x = ktory_katalog(nazwa);
	if (atrybuty[x].nazwa == (nazwa))
	{
		if (!atrybuty[x].zamek.lock(*process)) return;
			atrybuty[x].nazwa = "";
			atrybuty[x].rozmiar = 0;
			atrybuty[x].status = false;
			atrybuty[x].jap1 = 0;
			atrybuty[x].zapisany = false;
	}


	iloscWolnegoMiejsca();



	int buffor1;


	buffor = szukanieWolnegoJap();
	buffor1 = wolnyKatalog();



	//uzupelnienie wpisow do katalogu
	atrybuty[buffor1].nazwa = nazwa;
	atrybuty[buffor1].status = true;
	atrybuty[buffor1].jap1 = buffor;
	atrybuty[buffor1].rozmiar = 0;
	atrybuty[buffor1].zapisany = false;
	fat[buffor] = -1;
	data = dane1 + data;
	int jap1;
	int nastepnyJap;
	double dlugosc;
	double count_jap = 0;

	dlugosc = data.length();
	count_jap = ceil(dlugosc / 64);
	//   std::cout<<("DLUGOSC JAP "+count_jap);
	// Czy katalog wolny?  
	if (ktory_katalog(nazwa) != -1) {
		if (atrybuty[ktory_katalog(nazwa)].zapisany == false)
			atrybuty[ktory_katalog(nazwa)].zapisany = true;

		if (file_jap(nazwa) != -1) {
			if ((spacefree) > dlugosc) {
				jap1 = file_jap(nazwa);

				//DLA PIERWSZEGO 
				//	std::cout<<("pocz¹tek pliku "+jap1);
				char * datachar = new char[data.size() + 1];
				strcpy(datachar, data.c_str());
				for (int q = 0; q < data.length() && q < 64; q++) {
					//if (k <= dlugosc - 1) {
					dysk[q + jap1 * 64] = datachar[q];
					//std::cout<<(q+jap1*64+" -> "+dysk[q+jap1*64]);

				}
				//DLA WIECEJ
				if (count_jap > 1) {
					for (int j = 1; j <= count_jap - 1; j++) {
						nastepnyJap = szukanieWolnegoJap();
						//std::cout<<("WOLNY NEXT JAP "+nastepnyJap);
						fat[nastepnyJap] = -1;
						fat[jap1] = nastepnyJap;
						jap1 = nastepnyJap;
						for (int q = 0; q < 64 && q < data.length() - j * 64; q++) {
							dysk[q + jap1 * 64] = datachar[q + j * 64];
							//	std::cout<<(q+jap1*64+" -> "+dysk[q+jap1*64]);
						}

					}
				}
				std::cout << ("Wpisanie do pliku pomyslne");
				atrybuty[ktory_katalog(nazwa)].rozmiar = data.length();

			}
			else std::cout << ("Za malo miejsca na dysku");
		}
		else  std::cout << ("Nie mozna nadpisac danych");
	}
	else std::cout << ("Blad! Plik nie istnieje");
	iloscWolnegoMiejsca();

}
/*public void dopiszDoPliku(std::string nazwa, std::string ext, std::string data)//naprawoc
{
if(file_jap(nazwa,ext) != -1)
{
int jap = file_jap(nazwa,ext);
int nextjap;
int ostatniJap = 0;
int l;
int how;
double lenght;
int nastepnyJap;
double count_jap;
int rozmiar = atrybuty[jap].rozmiar;
std::cout<<(rozmiar);
while(jap != -1)
{
nextjap = fat[jap];
if(nextjap == -1)
{
ostatniJap = jap;
}
jap = nextjap;
}
how =wolnyJap(ostatniJap);
lenght = data.length();
std::cout<<(lenght);
count_jap = Math.ceil((lenght - how)/64);
if(atrybuty[ktory_katalog(nazwa,ext)].zapisany == true)
{
if (spacefree > (lenght - how))
{
atrybuty[ktory_katalog(nazwa, ext)].rozmiar += data.length();
l = 0;
char datachar[] = data.toCharArray();
for( int i =((ostatniJap *64)+rozmiar) ; i<(ostatniJap *64) + (64 - how) + how;i++ )
{
if(l<lenght)
{
dysk[i] = datachar[l];
l++;
}
}
for(int j = 1; j <= count_jap*64; j++)
{
std::cout<<("oetka");
nastepnyJap = szukanieWolnegoJap();
fat[nastepnyJap] = -1;
fat[ostatniJap] = nastepnyJap;
ostatniJap = nastepnyJap;
//
for(int z=0;z< 64 && z < data.length()-j*64;z++)
{
if(l < lenght)
{
dysk[z+jap*64+rozmiar] = datachar [z+j*64];
l++;
}
}
}
std::cout<<("Dopisanie pomyslnie wykonano");
iloscWolnegoMiejsca();
}
else
{
std::cout<<("Za malo miejsca na dysku");
iloscWolnegoMiejsca();
}
}
else
{
std::cout<<("Plik nie zostal wypelniony");
}
}
else
{
std::cout<<("Plik o podanej nazwie nie istnieje");
}
}*/

int Disc::wolnyJap(int nr_jap)
{
	int l = 0;
	for (int j = 0; j<nr_jap * 64; j++)
	{
		if (dysk[j] == 0)
		{
			l++;
		}
	}
	return l;
}
int Disc::ktory_katalog(std::string nazwa)
{
	for (int i = 0; i<64; i++)
	{
		if (atrybuty[i].nazwa == (nazwa))
		{
			return i;
		}
	}
	return -1;
}
int Disc::wolnyKatalog()
{
	for (int i = 0; i<64; i++)
	{
		if (atrybuty[i].status == false)
		{
			return i;
		}

	}
	return -1;
}

bool Disc::nazwaIstnieje(std::string nazwa)
{
	for (int i = 0; i<64; i++)
	{
		if (atrybuty[i].nazwa == (nazwa))
		{
			return false;
		}
	}
	return true;
}

int Disc::szukanieWolnegoJap()
{
	for (int i = 0; i<64; i++)
	{
		if (fat[i] == 0)
		{
			return i;
		}
	}
	return -1;
}
