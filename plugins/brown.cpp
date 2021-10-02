/*
 * Copyright (C) 2004,2005   Robert Nowotniak <robercik@stud.ics.p.lodz.pl>
 * Copyright (C) 2004,2005   Micha³ Ostrowski <mostrow@stud.ics.p.lodz.pl>
 *
 */
#include "common.h"
#include "komorka.h"
#include "sasiedztwo.h"

/*
 * S:1357
 * B:1357
 */

extern "C" int
funkcja
(const Warunki_Srodowiska *W, const Sasiedztwo_Moora *S, int stan)
{
	if (stan != 0)
		return 1;

	if (Zlicz_Sasiadow_W_Stanie(S, 2) == 1)
		return (rand() % 4) ? 0 : 2;
	else
		return 0;
}


