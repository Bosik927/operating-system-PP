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
//#include "Interpreter.h"
//#include "RAM.h"
#include "ProcessManagement.h"
enum Polecenia
{
	go, cp, dp, sp, mc, BLAD,
	ls, cf, wf, df, rf, reff, apf, EXIT, HELP
};
class Shell {
public:
	Shell() {}
	Polecenia convert(const std::string &str);
	bool is_number(const std::string &s);
	std::string text_to_string();
	void shell();
	void logo();

//	ProcessManagement processManagment;
	//RAM ram;
	Disc disc;
//	Komunikacja komunikacja;
//	Interpreter interpreter;


};






