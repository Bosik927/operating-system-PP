#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <string>
#include <iostream>
#include <math.h>
#include "Mutex.h"
#include "PCB.h"



class Tab_Fat {
public:
	std::string nazwa = "";						// nazwa
	bool status;					// status
	bool zapisany;					// Czy plik zapisany				
	int jap1;						// numer pierwszego jap
	int rozmiar;						// rozmiar plik
	Mutex zamek;									//Mutex zamek;

};

class Disc {

public:



	static const  int FFFF = -1;
	int rozmiarDysku = 512; // rozmiar dysku
	char dysk[512];				//dysk
	int fat[64];					//tablica fat 64 bity
	Tab_Fat atrybuty[64];		//wpis do katlogu glownego
	int spacefree = rozmiarDysku;						//wlne miejsce`


	Disc();
	void wys();
	std::string zawartoscDisc();
	std::string zawartoscPlik(std::string nazwa);


	//void tworzeniaPliku(std::string nazwa, PCB* process);
	void otworzPlik(std::string nazwa, PCB* process);
	void zamknijPlik(std::string nazwa, PCB*process);
	void tworzeniaPliku(std::string nazwa);
	void wpisywanieDoPliku(std::string nazwa, std::string data);
	void wpisywanieDoPliku(std::string nazwa, std::string data, PCB* process);
	int file_jap(std::string nazwa);
	int wolneMiejsceDysk();
	void usuwaniePliku(std::string nazwa);
	void usuwaniePliku(std::string nazwa, PCB* process);
	void wyswietlaPliki();
	void iloscWolnegoMiejsca();

	void drukujDysk(std::string nazwa);
	void www();
	void dopiszDoPliku(std::string nazwa, std::string data);
	void dopiszDoPliku(std::string nazwa, std::string data, PCB* process);
	int wolnyJap(int nr_jap);
	int ktory_katalog(std::string nazwa);
	int wolnyKatalog();
	bool nazwaIstnieje(std::string nazwa);
	int szukanieWolnegoJap();
	void zmianaNazwy(std::string nazwa, std::string newname);
	void zmianaNazwy(std::string nazwa, std::string newname, PCB* process);
	void stan_zamka(std::string a);
};