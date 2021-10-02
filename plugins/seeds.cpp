/*
 * Copyright (C) 2004,2005   Robert Nowotniak <robercik@stud.ics.p.lodz.pl>
 * Copyright (C) 2004,2005   Micha³ Ostrowski <mostrow@stud.ics.p.lodz.pl>
 *
 */
#include "common.h"
#include "komorka.h"
#include "sasiedztwo.h"

/*
 * S:
 * B:2
 */

extern "C" int
funkcja
(const Warunki_Srodowiska *W, const Sasiedztwo_Moora *S, int stan)
{
	return !stan && Zlicz_Niemartwych_Sasiadow(S) == 2;
}


