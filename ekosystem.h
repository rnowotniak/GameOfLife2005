/*
 * Copyright (C) 2004,2005   Robert Nowotniak <robercik@stud.ics.p.lodz.pl>
 * Copyright (C) 2004,2005   Micha³ Ostrowski <mostrow@stud.ics.p.lodz.pl>
 *
 */
#ifndef __HAVE_EKOSYSTEM_H
#define __HAVE_EKOSYSTEM_H 1

#include <cstdio>
#include "life.h"
#include "pole.h"
#include "tablica_pol.h"

class Tablica_Pol;
class Komorka;
class Warunki_Srodowiska;


class Opcje {
	bool _losowe_komorki;
	public:
		bool losowe_komorki() const
			{ return _losowe_komorki; }
		void losowe_komorki(bool l)
			{ _losowe_komorki = l; }
};


class Ekosystem {
	private:
		Tablica_Pol *tablica;
		Tablica_Pol *bufor;

		void zamien_tablice();

	public:
		Opcje opcje;

		Ekosystem(int szerokosc, int wysokosc);
		~Ekosystem();

		void generacja();
		void Dodaj_Uklad_Komorek(FILE *Plik, int x, int y);

		void Ustaw_Komorke(const Komorka *K, int x, int y);
		void Ustaw_Srodowisko(const Warunki_Srodowiska *E, int x, int y);
		void Ustaw_Stan(int S, int x, int y);

		void Usmierc_Komorki();
		void Wypelnij_Caly(const Komorka *K);

		int Podaj_Stan(int x, int y) const;
		const Warunki_Srodowiska* Podaj_Srodowisko(int x, int y) const;
		Tablica_Pol* podaj_tablice();

		void Wczytaj(FILE *Plik);
		void Zapisz(FILE *Plik) const;

		void Wczytaj_LIF(FILE *Plik, int wzg_x, int wzg_y, int stan);
		void Zapisz_LIF(FILE *Plik, int wzg_x, int wzg_y) const;
};




inline Tablica_Pol* Ekosystem::podaj_tablice()
{
	return tablica;
}


inline int
Ekosystem::
Podaj_Stan(int x, int y) const
{
	const Komorka *k;
	const Pole *p;

	if ((p = (*tablica)(x,y)) && (k = p->komorka))
		return k->podaj_stan();
	else  {
		// Na tym polu nie ma komórki
		return 0;
	}
}

inline
const Warunki_Srodowiska*
Ekosystem::
Podaj_Srodowisko(int x, int y) const
{
	const Pole *p;

	if ((p = (*tablica)(x,y)))
		return p->Podaj_Srodowisko();
	else
		return 0;
}

inline void
Ekosystem::
Ustaw_Komorke(const Komorka *K, int x, int y)
{
	Pole *p;

	if ((p = (*tablica)(x,y)))
		p->komorka = K;
}


inline void
Ekosystem::
Ustaw_Stan(int S, int x, int y)
{
	Pole *p;
	const Komorka *k;

	if ((p = (*tablica)(x,y)) && (k = p->komorka))
		p->komorka = Fabryka_Komorek::Nowa_Komorka(k->podaj_typ(), S);
}

#endif /* __HAVE_EKOSYSTEM_H */
