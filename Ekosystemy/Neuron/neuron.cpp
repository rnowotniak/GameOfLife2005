/*
 * Copyright (C) 2004,2005   Robert Nowotniak <robercik@stud.ics.p.lodz.pl>
 * Copyright (C) 2004,2005   Micha³ Ostrowski <mostrow@stud.ics.p.lodz.pl>
 *
 */
#include "common.h"
#include "komorka.h"
#include "sasiedztwo.h"

extern "C" int
funkcja
(const Warunki_Srodowiska *W, const Sasiedztwo_Moora *S, int stan)
{
	if (stan == 5)
		return 6;
	if (stan == 6)
		return 4;

	if (stan == 4 && Zlicz_Sasiadow_W_Stanie(S, 5))
		return 5;

	return stan;
}


