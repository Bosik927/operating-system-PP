// test.cpp : Defines the entry point for the console application.
//
#include "plikiFAT.h"


int main()
{
	Disc dysk;
	dysk.tworzeniaPliku("plik");
	dysk.dopiszDoPliku("plik", "siemkasiemkasiemkasiemkasiemkasiemkasiemkasiemkasiemkasiemkasiemkasiemkasiemkasiemka");
	dysk.tworzeniaPliku("p2");
	dysk.dopiszDoPliku("p2", "siemkasiemkasiemkasiemkasiemkasiemkasiemkasiemkasiemkasiemkasiemkasiemkasiemkasiemka");
	dysk.wyswietlaPliki();
	dysk.drukujDysk("plik");
	dysk.drukujDysk("p");
	dysk.wolnyKatalog();
	std::cin.ignore(3);
	return 0;
}

