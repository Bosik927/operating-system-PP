#pragma once

#include<array>

class ID_Manager //Menad¿er numerów ID, zawiera tablica bitow¹ zawieraj¹c¹ informacje czy konkretne ID jest dostêpne; 0 - dostêpne, 1 - niedostêpne
{
private:
	const int AmountOfID = 1000;//wielkoœæ tablicy bitowej, okreœla dopuszczalny zakres ID mo¿liwych do nadania, a wiêc tak¿e maksymaln¹ liczbê procesów
	std::array<bool, 1000> FreeIdArray;
public:
	ID_Manager()
	{
		FreeIdArray.fill(0);
	}
	int PickID();
	void ClearID(int ID);
};