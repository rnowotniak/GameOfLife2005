/*
 * Copyright (C) 2004,2005   Robert Nowotniak <robercik@stud.ics.p.lodz.pl>
 * Copyright (C) 2004,2005   Micha³ Ostrowski <mostrow@stud.ics.p.lodz.pl>
 *
 */
#include "common.h"
#include "komorka.h"
#include "sasiedztwo.h"

/*
 * S:1358
 * B:357
 */

extern "C" int
funkcja
(const Warunki_Srodowiska *W, const Sasiedztwo_Moora *S, int stan)
{
	int Sasiedzi8 = 0;
	int Sasiedzi9 = 0;
	const Komorka *k;

	if ((k = S->Sasiad_Polnocny())) {
		if (k->podaj_typ() == 2 && k->podaj_stan() == 5)
			// Cia³o komórki nerowowej z impulsem
			return 9;
		Sasiedzi8 += k->podaj_stan() == 8,
		Sasiedzi9 += k->podaj_stan() == 9;
	}
	if ((k = S->Sasiad_Poludniowy())) {
		if (k->podaj_typ() == 2 && k->podaj_stan() == 5)
			return 9;
		Sasiedzi8 += k->podaj_stan() == 8,
		Sasiedzi9 += k->podaj_stan() == 9;
	}
	if ((k = S->Sasiad_Zachodni())) {
		if (k->podaj_typ() == 2 && k->podaj_stan() == 5)
			return 9;
		Sasiedzi8 += k->podaj_stan() == 8,
		Sasiedzi9 += k->podaj_stan() == 9;
	}
	if ((k = S->Sasiad_Wschodni())) {
		if (k->podaj_typ() == 2 && k->podaj_stan() == 5)
			return 9;
		Sasiedzi8 += k->podaj_stan() == 8,
		Sasiedzi9 += k->podaj_stan() == 9;
	}
	if ((k = S->Sasiad_Polnocno_Zachodni())) {
		if (k->podaj_typ() == 2 && k->podaj_stan() == 5)
			return 9;
		Sasiedzi8 += k->podaj_stan() == 8,
		Sasiedzi9 += k->podaj_stan() == 9;
	}
	if ((k = S->Sasiad_Polnocno_Wschodni())) {
		if (k->podaj_typ() == 2 && k->podaj_stan() == 5)
			return 9;
		Sasiedzi8 += k->podaj_stan() == 8,
		Sasiedzi9 += k->podaj_stan() == 9;
	}
	if ((k = S->Sasiad_Poludniowo_Zachodni())) {
		if (k->podaj_typ() == 2 && k->podaj_stan() == 5)
			return 9;
		Sasiedzi8 += k->podaj_stan() == 8,
		Sasiedzi9 += k->podaj_stan() == 9;
	}
	if ((k = S->Sasiad_Poludniowo_Wschodni())) {
		if (k->podaj_typ() == 2 && k->podaj_stan() == 5)
			return 9;
		Sasiedzi8 += k->podaj_stan() == 8,
		Sasiedzi9 += k->podaj_stan() == 9;
	}

	if (stan == 8 || stan == 9)
		switch (Sasiedzi8 + Sasiedzi9) {
			case 1:
			case 3:
			case 5:
			case 8:
				return 8;
		}
	else if (stan == 7)
		switch (Sasiedzi8 + Sasiedzi9) {
			case 3:
			case 5:
			case 7:
				return 9;
		}

	return 7;
}


