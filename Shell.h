#pragma once
#include "Interpreter.h"
#include "ProcessManagement.h"

class Shell {
public:
	Interpreter inter;
	ProcessManagement man;

	Shell();
	void shell();

};