#include<iostream>
#include "ID_Manager.h"


int ID_Manager::PickID()
{
	for (int i = 0; i < AmountOfID; i++)
	{
		if (FreeIdArray[i] == 0)
		{
			FreeIdArray[i] = 1;
			return i;
		}
	}
	std::cout << "Wszystkie numery ID sa wykorzystane" << std::endl;
	return -1;
}

void ID_Manager::ClearID(int ID)
{
	FreeIdArray[ID] = 0;
}
