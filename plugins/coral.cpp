/*
 * Copyright (C) 2004,2005   Robert Nowotniak <robercik@stud.ics.p.lodz.pl>
 * Copyright (C) 2004,2005   Micha³ Ostrowski <mostrow@stud.ics.p.lodz.pl>
 *
 */
#include "common.h"
#include "komorka.h"
#include "sasiedztwo.h"

/*
 * S:45678
 * B:3
 */

extern "C" int
funkcja
(const Warunki_Srodowiska *W, const Sasiedztwo_Moora *S, int stan)
{
	int Sasiedzi = Zlicz_Niemartwych_Sasiadow(S);

	switch (Sasiedzi) {
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
			return stan;
		case 3:
			return 1;
		default:
			return 0;
	}
}


