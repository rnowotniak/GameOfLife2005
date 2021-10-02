/*
 * Copyright (C) 2004,2005   Robert Nowotniak <robercik@stud.ics.p.lodz.pl>
 * Copyright (C) 2004,2005   Micha� Ostrowski <mostrow@stud.ics.p.lodz.pl>
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
	int Sasiedzi = Zlicz_Niemartwych_Sasiadow(S);

	if (stan)
		switch (Sasiedzi) {
			case 1:
			case 3:
			case 5:
			case 8:
				return 1;
		}
	else
		switch (Sasiedzi) {
			case 3:
			case 5:
			case 7:
				return 1;
		}

	return 0;
}


