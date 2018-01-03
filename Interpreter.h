#pragma once
#include <iostream>
#include <string>
// #include "Dysk.h"
// #include "ProcessManagement.h"
using namespace std;

enum Rozkazy {
	AD, // AD A B					(dodaje do rejestrA zawarto�� rejestrB) +
	AX, // AX A 10					(dodaje liczby do rejestru) +
	SB, // SB A B					(odejmuje od rejestrA zawarto�� rejestrB) +
	MU, // MU A B					(mnozy rejestrA przez rejestrB) +
	MX, // MX A 100					(mnozy rejestr przez liczbe) +
	MV, // MV A B					(kopiuje warto�� rejestruB do rejestruA) +
	MZ, // MZ n 					(zapisuje do pami�ci zawarto�� rejestru pod wskazanym adresem) ?
	MO, // MO A n					(umieszcza w rejestrze wartosc n) ?
	MY, //							(umieszcza w rejestrze zawarto�� pamietan� pod wskazanym adresem) ?
	JP, // JP n						(skacze do innego rozkazu poprzez zmian� licznika) +
	JZ,	//							(skok przy zerowej zawarto�ci rejestru b�d�cego argumentem) ?
	CF, // CF nazwa_pliku			(tworzy plik o podanej nazwie)
	WF, // WF nazwa_pliku tre��
	DF, // DF nazwa_pliku			(usuwa plik o danej nazwie)
	RF, // RF nazwa_pliku tre��
	AF, // AF nazwa_pliku tre��     (nadpisuje plik o danej nazwie)
	CP, // CP nazwa sciezka			(tworzenie procesu)
	DP, // DP nazwa
	RP, // RP nazwa
	RM, // adres_w_pami�ci			(czytanie komunikatu)
	SM, // odbiorca tre��
	HL	// ko�czy program
};

Rozkazy convert(const string& operacja);

// TODO:
// - Rozkazy zwi�zane z procesami // Adam
// - Rozkazy zwi�zane z komunikacj� // Adrian
// - Rozkaz JUMP
// - 3 programy asemblerowe

class Interpreter
{
private:
	bool isLabel(string &program);
	// private PCB PCBbox; <--- PCBbox przechowuje nazwe procesu
	// private RAM ram;    <--- nasze rozkazy
	// private Disc disc; <--- pliki
	// private ProcessManagement processmanagement; <--- proces
	// Komunikacja komunikacja; <--- komunikacja
	Rozkazy rozkaz;
public:
	bool run();
	Interpreter(/*RAM &ram, FileSystem &filesystem, ProcessManagement &processmanagement*/);
};
