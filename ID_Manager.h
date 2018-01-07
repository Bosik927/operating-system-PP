#pragma once
#include<array>

class ID_Manager //Menad�er numer�w ID, zawiera tablica bitow� zawieraj�c� informacje czy konkretne ID jest dost�pne; 0 - dost�pne, 1 - niedost�pne
{
private:
	const int AmountOfID = 1000;//wielko�� tablicy bitowej, okre�la dopuszczalny zakres ID mo�liwych do nadania, a wi�c tak�e maksymaln� liczb� proces�w
	std::array<bool, 1000> FreeIdArray;
public:
	ID_Manager();
	int PickID();
	void ClearID(int ID);
};