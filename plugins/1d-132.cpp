/*
 * Copyright (C) 2004,2005   Robert Nowotniak <robercik@stud.ics.p.lodz.pl>
 * Copyright (C) 2004,2005   Micha³ Ostrowski <mostrow@stud.ics.p.lodz.pl>
 *
 */
#include "common.h"
#include "komorka.h"
#include "sasiedztwo.h"

/*
 * Regu³a 132 -- automat stabilny (lub periodyczny)
 */

extern "C" int
funkcja
(const Warunki_Srodowiska *W, const Sasiedztwo_Moora *S, int stan)
{
	if (stan)
		return 1;

	const Komorka *k1, *k2, *k3;

	k1 = S->Sasiad_Poludniowo_Zachodni();
	k2 = S->Sasiad_Poludniowy();
	k3 = S->Sasiad_Poludniowo_Wschodni();

	if (!k1 || !k2 || !k3)
		return 0;

	int s1 = k1->podaj_stan(), s2 = k2->podaj_stan(), s3 = k3->podaj_stan();

	if (s1 && s2 && s3)
		return 1;
	if (!s1 && s2 && !s3)
		return 1;

	return 0;
}


