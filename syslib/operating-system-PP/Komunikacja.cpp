#include "Komunikacja.h"

Komunikacja::Komunikacja() {}

Komunikacja::Komunikacja(ProcessManagement *Proces)
{
	this->Proces = Proces;
}

void Komunikacja::write(string id, string msg)
{
	lock->lock(*(Proces)->getPCB(Proces->getIdFromName(id)));
	mkfif.zapisz(msg);
	lock->unlock(*(Proces)->getPCB(Proces->getIdFromName(id)));
}

//void Komunikacja::read(string id)
//{
//	lock->lock(*(Proces)->getPCB(Proces->getIdFromName(id)));
//	mkfif.odczytaj();
//	mkfif.fifo.open(mkfif.sciezka, ios::trunc);
//	mkfif.fifo.close();
//	lock->unlock(*(Proces)->getPCB(Proces->getIdFromName(id)));
//}

void Komunikacja::read(string id, int iloscz)
{
	lock->lock(*(Proces)->getPCB(Proces->getIdFromName(id)));
	mkfif.odczytaj(iloscz);
	mkfif.fifo.open(mkfif.sciezka, ios::trunc);
	mkfif.fifo.close();
	lock->unlock(*(Proces)->getPCB(Proces->getIdFromName(id)));
}


