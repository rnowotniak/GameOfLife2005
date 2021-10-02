/*
 * Copyright (C) 2004,2005   Robert Nowotniak <robercik@stud.ics.p.lodz.pl>
 * Copyright (C) 2004,2005   Micha� Ostrowski <mostrow@stud.ics.p.lodz.pl>
 *
 */
#include "common.h"
#include "komorka.h"
#include "sasiedztwo.h"

/*
 * 3-stanowe kom�rki Conwayowskie
 *
 *   Kom�rki, kt�re o�y�y w danej generacji maj� odmienny stan
 *   ni� te, kt�re przetrwa�y.
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


