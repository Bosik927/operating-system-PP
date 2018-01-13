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
	go, cp, dp, sp, mc, BLAD, sproc, sprocn, sprocid,ef,
	ls, cf, wf, df, rf, reff, apf, EXIT, HELP
};
class Shell {
public:
	RAM ram;
	ProcessManagement pm = ProcessManagement(&ram);;
	Disc disc;
	Komunikacja kom;
	Interpreter interpreter;


	Disc *d;


	Shell() 
	{
		interpreter = Interpreter(&pm, &kom,&disc,&ram);
		
	}
	Polecenia convert(const std::string &str);
	bool is_number(const std::string &s);
	std::string text_to_string();
	void shell();
	void logo();




};






