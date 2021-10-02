/*
 * Copyright (C) 2004,2005   Robert Nowotniak <robercik@stud.ics.p.lodz.pl>
 * Copyright (C) 2004,2005   Micha³ Ostrowski <mostrow@stud.ics.p.lodz.pl>
 *
 */
#include "common.h"
#include "komorka.h"
#include "sasiedztwo.h"

/*
 * 3-stanowe komórki Conwayowskie
 *
 *   Komórki, które o¿y³y w danej generacji maj± odmienny stan
 *   ni¿ te, które przetrwa³y.
 *
 * S:23
 * B:3
 */

extern "C" int
funkcja
(const Warunki_Srodowiska *W, const Sasiedztwo_Moora *S, int stan)
{
	int Zywi_Sasiedzi = Zlicz_Niemartwych_Sasiadow(S);
	const Komorka *k;

	if (stan == 0 && Zywi_Sasiedzi == 3)
		return 2;

	if (stan && (Zywi_Sasiedzi == 2 || Zywi_Sasiedzi == 3))
		return 1;

	return 0;
}


