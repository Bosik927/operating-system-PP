#pragma once
#include <iostream>
#include <string>
#include "ProcessManagement.h"
#include "PCB.h"
#include "Scheduler.h"
#include "plikiFAT.h"
#include "Komunikacja.h"
#include "RAM.h"
using namespace std;
enum Rozkazy {
	AD, // AD A B					(dodaje do rejestrA zawartoœæ rejestrB) +
	AX, // AX A 10					(dodaje liczby do rejestru) +
	SB, // SB A B					(odejmuje od rejestrA zawartoœæ rejestrB) +
	MU, // MU A B					(mnozy rejestrA przez rejestrB) +
	MX, // MX A 100					(mnozy rejestr przez liczbe) +
	MV, // MV A B					(kopiuje wartoœæ rejestruB do rejestruA) +
	MZ, // MZ n 					(zapisuje do pamiêci zawartoœæ rejestru pod wskazanym adresem) ?
	MO, // MO A n					(umieszcza w rejestrze wartosc n) ?
	MY, //							(umieszcza w rejestrze zawartoœæ pamietan¹ pod wskazanym adresem) ?
	JP, // JP n						(skacze do innego rozkazu poprzez zmianê licznika) +
	JZ,	//							(skok przy zerowej zawartoœci rejestru bêd¹cego argumentem) ?
	CF, // CF nazwa_pliku			(tworzy plik o podanej nazwie)
	WF, // WF nazwa_pliku treœæ
	DF, // DF nazwa_pliku			(usuwa plik o danej nazwie)
	RF, // RF nazwa_pliku treœæ
	AF, // AF nazwa_pliku treœæ     (nadpisuje plik o danej nazwie)
	CP, // CP nazwa sciezka			(tworzenie procesu)
	DP, // DP nazwa
	RP, // RP nazwa
	RM, // adres_w_pamiêci			(czytanie komunikatu)
	SM, // odbiorca treœæ
	HL	// koñczy program
};

Rozkazy convert(const string& operacja);

// TODO:
// - Rozkaz zapisywania 
// - 3 programy asemblerowe

class Interpreter
{
private:
	bool isLabel(string &program);
	Disc *disc; //<--- pliki
	ProcessManagement *processmanagement; //<--- proces
	Komunikacja *komunikacja; // <--- komunikacja
	Rozkazy rozkaz;
	string program="AX A 9"; // rozkaz pobierany z ramu
public:
	void run(PCB* PCBbox);
	Interpreter() {}
	Interpreter(ProcessManagement* pm, Komunikacja* km, Disc* dc)
	{
		this->processmanagement = pm;
		this->komunikacja = km;
		this->disc = dc;
	}
};
