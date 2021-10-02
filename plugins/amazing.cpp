/*
 * Copyright (C) 2004,2005   Robert Nowotniak <robercik@stud.ics.p.lodz.pl>
 * Copyright (C) 2004,2005   Micha� Ostrowski <mostrow@stud.ics.p.lodz.pl>
 *
 */
#include "common.h"
#include "komorka.h"
#include "sasiedztwo.h"

/*
 * S:12345
 * B:3
 */

extern "C" int
funkcja
(const Warunki_Srodowiska *W, const Sasiedztwo_Moora *S, int stan)
{
	int Sasiedzi = Zlicz_Niemartwych_Sasiadow(S);

	if (stan)
		switch (Sasiedzi) {
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
				return 2;
		}
	else
		switch (Sasiedzi) {
			case 3:
				return 1;
		}

	return 0;
}


