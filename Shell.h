#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <Windows.h>
#include "plikiFAT.h"
enum Polecenia
{
	GO, CP, DP, SP, MC, BLAD,
	LS, CF, WF, DF, RF, REF, APF, EXIT, HELP
};
class Shell {
public:
	
	Polecenia convert(const std::string &str);
	bool is_number(const std::string &s);
	std::string text_to_string();
	void shell();
	void logo();
	Disc dysk;
	
};


