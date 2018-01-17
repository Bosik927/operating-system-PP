#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <Windows.h>
#include "plikiFAT.h"
#include "PCB.h"
#include "Interpreter.h"
#include "RAM.h"
#include "ProcessManagement.h"
enum Polecenia
{
	go, cp, dp, mc, BLAD, sproc, sprocn, sprocid,ef,run,sz,
	ls, cf, wf, df, rf, reff, apf, EXIT, HELP
};
class Shell {
public:
	RAM ram;
	ProcessManagement pm = ProcessManagement(&ram);;
	Disc disc;
	Komunikacja kom = Komunikacja(&pm);
	Interpreter interpreter;

	Polecenia k;
	std::string wczytywany_string;
	std::vector<std::string> vector_str;
	std::vector<std::string> vector_skrypt;
	std::string pom1, pom2;
	bool a;


	Shell() 
	{
		interpreter = Interpreter(&pm, &kom,&disc,&ram);
		this->a = true;
	
	}
	Polecenia convert(const std::string &str);
	bool is_number(const std::string &s);
	void shell();
	void logo();
	void interpret(std::string a);
	void odczyt_z_pliku(std::string a);


};






