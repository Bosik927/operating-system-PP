// test.cpp : Defines the entry point for the console application.
//
#include "plikiFAT.h"


int main()
{
	Disc dysk;
	dysk.tworzeniaPliku("plik");
	dysk.dopiszDoPliku("plik", "siemka");
	dysk.wyswietlaPliki();
	dysk.drukujDysk("plik");
	dysk.wolnyKatalog();
	std::cin.ignore(3);
	return 0;
}

