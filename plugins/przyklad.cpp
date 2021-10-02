/*
 * Copyright (C) 2004,2005   Robert Nowotniak <robercik@stud.ics.p.lodz.pl>
 * Copyright (C) 2004,2005   Micha� Ostrowski <mostrow@stud.ics.p.lodz.pl>
 *
 */
/*
 *
 * U�ytkownik mo�e dostarczy� skompilowany modu� z w�asn� definicj�
 * funkcji przej�cia. Ten przykladowy plik pokazuje, jak mo�e
 * wygl�da� kod �r�d�owy takiego modu�u.
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

	// Kom�rka umiera przy ujemnej temperaturze
	if (W->temperatura() < 0)
		return 0;

	// Kom�rka przyjmuje stan 1 przy du�ym nas�onecznieniu i wilgotno�ci
	if (W->oswietlenie() > 50 && W->wilgotnosc() > 50)
		return 1;

	// Kom�rka przyjmuje stan 2, je�li jej p�nocy s�siad te� jest w takim stanie
	if ((k = S->Sasiad_Polnocny()) && k->podaj_stan() == 2)
		return 2;

	// Kom�rka przyjmuej stan 3, je�li ma ponad pi�ciu niemartwych s�siad�w
	if (Zlicz_Niemartwych_Sasiadow(S) > 5)
		return 3;

	// W pozosta�ych przypadkach kom�rka obumiera
	return 0;
}


