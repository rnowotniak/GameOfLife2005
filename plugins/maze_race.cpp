/*
 * Copyright (C) 2004,2005   Robert Nowotniak <robercik@stud.ics.p.lodz.pl>
 *
 * Automat komórkowy mojego pomys³u:
 * Stan komórki decyduje o jednym z dwu rodzajów zachowañ:
 *    niektóre komórki buduj± chaotyczny labirynt
 *    inne komórki próbuj± z niego uciec (znale¼æ wyj¶æie)
 *
 */
#include "common.h"
#include "komorka.h"
#include "sasiedztwo.h"

/*
 *
 * Takie komórki stworz± labirynt:
 *		 S:12345
 *		 B:3
 *
 * Stany:
 * 	0  --  martwa
 * 	1  --  ¶ciana
 * 	2  --  nowa ¶ciana
 * 	3  --  uciekinier1
 * 	4  --  uciekinier2
 *
 */

// maze race

extern "C" int
funkcja
(const Warunki_Srodowiska *W, const Sasiedztwo_Moora *S, int stan)
{
	int Sasiedzi = 0;
	const Komorka *k;
	int ts;
	int sciany = 0;
	bool jest_uciekinier = false;

	if ((k = S->Sasiad_Polnocny()))
		if ((ts = k->podaj_stan()) == 1 || ts == 2)
			sciany++;
		else if (ts == 3)
			jest_uciekinier = true;
	if ((k = S->Sasiad_Polnocno_Wschodni()))
		if ((ts = k->podaj_stan()) == 1 || ts == 2)
			sciany++;
		else if (ts == 3)
			jest_uciekinier = true;
	if ((k = S->Sasiad_Wschodni()))
		if ((ts = k->podaj_stan()) == 1 || ts == 2)
			sciany++;
		else if (ts == 3)
			jest_uciekinier = true;
	if ((k = S->Sasiad_Poludniowo_Wschodni()))
		if ((ts = k->podaj_stan()) == 1 || ts == 2)
			sciany++;
		else if (ts == 3)
			jest_uciekinier = true;
	if ((k = S->Sasiad_Poludniowy()))
		if ((ts = k->podaj_stan()) == 1 || ts == 2)
			sciany++;
		else if (ts == 3)
			jest_uciekinier = true;
	if ((k = S->Sasiad_Poludniowo_Zachodni()))
		if ((ts = k->podaj_stan()) == 1 || ts == 2)
			sciany++;
		else if (ts == 3)
			jest_uciekinier = true;
	if ((k = S->Sasiad_Zachodni()))
		if ((ts = k->podaj_stan()) == 1 || ts == 2)
			sciany++;
		else if (ts == 3)
			jest_uciekinier = true;
	if ((k = S->Sasiad_Polnocno_Zachodni()))
		if ((ts = k->podaj_stan()) == 1 || ts == 2)
			sciany++;
		else if (ts == 3)
			jest_uciekinier = true;

	/*
	 * Niech ¶ciany maj± pierwszeñstwo
	 */

	if (stan == 1 || stan == 2)
		switch (sciany) {
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
				return 1;
		}
	else if (stan == 0) {
		if (sciany == 3)
			return 2;
		if (jest_uciekinier)
			return 3;
	} else if (stan == 4)
		return 0;
	else if (stan == 3)
		return 4;

	return 0;
}


