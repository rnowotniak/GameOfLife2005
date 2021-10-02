/*
 * Copyright (C) 2004,2005   Robert Nowotniak <robercik@stud.ics.p.lodz.pl>
 * Copyright (C) 2004,2005   Micha³ Ostrowski <mostrow@stud.ics.p.lodz.pl>
 *
 */
/*
 *
 * U¿ytkownik mo¿e dostarczyæ skompilowany modu³ z w³asn± definicj±
 * funkcji przej¶cia. Ten przykladowy plik pokazuje, jak mo¿e
 * wygl±daæ kod ¼ród³owy takiego modu³u.
 *
 */


#include "common.h"
#include "komorka.h"
#include "sasiedztwo.h"
#include "srodowisko.h"

extern "C" int
//Przykladowa_Funkcja_Przejscia
funkcja
(const Warunki_Srodowiska *W, const Sasiedztwo_Moora *S, int stan)
{
	int Zywi_Sasiedzi = Zlicz_Niemartwych_Sasiadow(S);
	const Komorka *k;

	// Komórka umiera przy ujemnej temperaturze
	if (W->temperatura() < 0)
		return 0;

	// Komórka przyjmuje stan 1 przy du¿ym nas³onecznieniu i wilgotno¶ci
	if (W->oswietlenie() > 50 && W->wilgotnosc() > 50)
		return 1;

	// Komórka przyjmuje stan 2, je¶li jej pó³nocy s±siad te¿ jest w takim stanie
	if ((k = S->Sasiad_Polnocny()) && k->podaj_stan() == 2)
		return 2;

	// Komórka przyjmuej stan 3, je¶li ma ponad piêciu niemartwych s±siadów
	if (Zlicz_Niemartwych_Sasiadow(S) > 5)
		return 3;

	// W pozosta³ych przypadkach komórka obumiera
	return 0;
}


