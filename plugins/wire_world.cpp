/*
 * Copyright (C) 2004,2005   Robert Nowotniak <robercik@stud.ics.p.lodz.pl>
 * Copyright (C) 2004,2005   Micha³ Ostrowski <mostrow@stud.ics.p.lodz.pl>
 *
 */
#include "common.h"
#include "komorka.h"
#include "sasiedztwo.h"

/*
 * Wired World
 *
 * Automat zaprojektowany w 1987 przez Briana Silvermana.
 * Proste regu³y pozwalaj± tworzyæ zupe³ni skomplikowane obwody elektryczne.
 *
 *
 * 	1,0,0,
 * 		0,0,0,0,0,0,0,0,0,0,   -- brak komorki
 * 		2,2,2,2,2,2,2,2,2,0,   -- przód elektronu
 * 		3,3,3,3,3,3,3,3,3,0,   -- ty³ elektronu
 * 		3,1,1,3,3,3,3,3,3      -- przewodnik
 */

extern "C" int
funkcja
(const Warunki_Srodowiska *W, const Sasiedztwo_Moora *S, int stan)
{
	int Sasiedzi = Zlicz_Niemartwych_Sasiadow(S);

	if (stan == 0)
		return 0;

	switch (stan) {
		case 0:
			return 0;
		case 1:
			return 2;
		case 2:
			return 3;
		case 3:
			switch (Zlicz_Sasiadow_W_Stanie(S, 1)) {
				case 1:
				case 2:
					return 1;
				default:
					return 3;
			}
		default:
			return 0;
	}
}


