#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Mutex.h"
#include "ProcessManagement.h"

using namespace std;

struct mkfifo
{
	string temp;
	string sciezka;
	ofstream fifo;
	mkfifo()
	{
		sciezka = "fifo.txt";
	}
	void zapisz(string msg)
	{
		fifo.open(sciezka, ios::app);
		if (fifo.is_open())
		{
			fifo << msg;
		}
		fifo.close();
	}
	//void odczytaj()
	//{
	//	ifstream fifo(sciezka);
	//	string linia;
	//	if (fifo.is_open())
	//	{
	//		while (getline(fifo, linia))
	//		{
	//			temp += linia;
	//		}
	//	}
	//	else
	//		cout << "Blad odczytania z pliku" << endl;
	//	cout << temp;
	//	cout << endl;
	//	fifo.close();
	//}
	void odczytaj(int iloscz)
	{
		ifstream fifo(sciezka);
		string linia;
		if (fifo.is_open())
		{
			while (getline(fifo, linia))
			{
				temp += linia;
			}
		}
		for (int i = 0; i < iloscz; i++)
			cout << temp[i];
		cout << endl;
		temp = temp.substr(iloscz, temp.size());
		fifo.close();
	}
};


class Komunikacja
{
public:
	ProcessManagement * Proces;
	Mutex lock;
public:
	Komunikacja();
	Komunikacja(ProcessManagement *Proces);
	vector<string> tab;
	mkfifo mkfif;
	void write(string id, string msg);
	//void read(string id);
	void read(string id, int iloscz);
};

