#include "Komunikacja.h"

Komunikacja::Komunikacja(ProcessManagement *Proces)
{
	this->Proces = Proces;
}

void Komunikacja::write(string id, string msg)
{
	lock->lock(*(Proces)->getPCB(Proces->getIdFromName(id)));
	mkfifo.zapisz(msg);
	lock->unlock(*(Proces)->getPCB(Proces->getIdFromName(id)));
}

void Komunikacja::read(string id)
{
	lock->lock(*(Proces)->getPCB(Proces->getIdFromName(id)));
	mkfifo.odczytaj();
	mkfifo.fifo.open(mkfifo.sciezka, ios::trunc);
	mkfifo.fifo.close();
	lock->unlock(*(Proces)->getPCB(Proces->getIdFromName(id)));
}

void Komunikacja::read(string id, int iloscz)
{
	lock->lock(*(Proces)->getPCB(Proces->getIdFromName(id)));
	mkfifo.odczytaj(iloscz);
	mkfifo.fifo.open(mkfifo.sciezka, ios::trunc);
	mkfifo.fifo.close();
	lock->unlock(*(Proces)->getPCB(Proces->getIdFromName(id)));
}
