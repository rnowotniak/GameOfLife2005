/*
 * Copyright (C) 2004,2005   Robert Nowotniak <robercik@stud.ics.p.lodz.pl>
 * Copyright (C) 2004,2005   Micha³ Ostrowski <mostrow@stud.ics.p.lodz.pl>
 *
 */
#ifndef __HAVE_POLE_H
#define __HAVE_POLE_H 1

#include "life.h"
#include "fabryka.h"

class Sasiedztwo_Moora;
class Warunki_Srodowiska;
class Komorka;

class Pole  {
	private:
		const Warunki_Srodowiska *srodowisko;
	public:
		Pole(Warunki_Srodowiska *E = 0, Komorka *K = 0);

		const Komorka *komorka;

		int cykl(Sasiedztwo_Moora *S);

		const Warunki_Srodowiska* Podaj_Srodowisko() const;
		void Ustaw_Srodowisko(const Warunki_Srodowiska *E);
};



inline void
Pole::Ustaw_Srodowisko(const Warunki_Srodowiska *E)
{
	srodowisko = E;
}

inline
const Warunki_Srodowiska* Pole::
Podaj_Srodowisko() const
{
	return srodowisko;
}

inline
Pole::Pole(Warunki_Srodowiska *E, Komorka *K)
	: komorka(K)
{
	if (E)
		srodowisko = E;
	else
		srodowisko = Fabryka_Warunkow_Srodowiska::Nowe_Warunki("Warunki domyslne");
}


inline int
Pole::
cykl(Sasiedztwo_Moora *S)
{
	return komorka->funkcja()(srodowisko, S, komorka->podaj_stan());
}


#endif /* __HAVE_POLE_H */
