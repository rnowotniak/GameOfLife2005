/*
 * Copyright (C) 2004,2005   Robert Nowotniak <robercik@stud.ics.p.lodz.pl>
 * Copyright (C) 2004,2005   Micha³ Ostrowski <mostrow@stud.ics.p.lodz.pl>
 *
 */
#include "common.h"
#include "komorka.h"
#include "sasiedztwo.h"

/*
 * Regu³y: /2/3
 */

extern "C" int
funkcja
(const Warunki_Srodowiska *W, const Sasiedztwo_Moora *S, int stan)
{
	if (stan == 1)
		return 2;
	if (stan == 2)
		return 0;
	if (Zlicz_Sasiadow_W_Stanie(S, 1) == 2)
		return 1;
	return 0;
}


