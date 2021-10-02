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
	int Sasiedzi = Zlicz_Niemartwych_Sasiadow(S);

	if (stan)
		switch (Sasiedzi) {
			case 2:
			case 3:
			case 4:
			case 5:
				return 3;
		}
	else
		switch (Sasiedzi) {
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
				return 2;
		}

	return 0;
}


