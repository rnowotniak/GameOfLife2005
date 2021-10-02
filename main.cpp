/*
 * Copyright (C) 2004,2005   Robert Nowotniak <robercik@stud.ics.p.lodz.pl>
 * Copyright (C) 2004,2005   Micha³ Ostrowski <mostrow@stud.ics.p.lodz.pl>
 *
 */
/*
 * W tym pliku jest tylko prosty, pocz±tkowy interfejs tekstowy,
 * który prawie nic nie oferuje!
 *
 * G³ównym interfejsem u¿ytkownika jest teraz GUI oparte na FLTK (--> fllife.cpp)!
 *
 *
 */

#include "life.h"
#include "ekosystem.h"
#include "komorka.h"
#include "fabryka.h"

//--------------------------------------------------------------------------------
//                                 DO TESTÓW
//--------------------------------------------------------------------------------
#include <time.h>
#include <sys/time.h>

#include <cstdio>
#include <cstdlib>
#include "tablica_pol.h"
void Wyswietl(Ekosystem *swiat)
{
	for (int y = 0; y < swiat->podaj_tablice()->podaj_wysokosc(); y++) {
		for (int x = 0; x < swiat->podaj_tablice()->podaj_szerokosc(); x++) {
			printf("%c", swiat->Podaj_Stan(x, y)?'X':'.');
		}
		printf("\n");
	}
	printf("\n");
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------



int main()
{
	/*
	 * Stworzenie ma³ego ¶wiata
	 */
	Ekosystem Swiat1(20, 20);


	// Wska¼nik na funkcjê Conwayowsk±
	Komorka::funkcja_przejscia Conway;


	// Po³o¿enie pliku z modu³em
	std::string wtyczka = std::string(KATALOG_WTYCZEK).append("/");
#ifdef LINUX
	wtyczka.append("conway.so");
#else
#ifdef WIN32
	wtyczka.append("conway.dll");
#endif
#endif

	
	// Za³adowanie modu³u
	Conway = Fabryka_Funkcji::Zaladuj_Funkcje(wtyczka);

	if (! Conway) {
		fprintf(stderr, "Niestety, ale modu³ z funkcj± przej¶cia siê nie za³adowa³.\n");
		return -1;
	}



	/*
	 * Utworzenie bardzo prostego uk³adu w ¦wiecie
	 */

	Fabryka_Komorek::Nowy_Rodzaj_Komorki(0, Conway);

	for (int y = 0; y < 20; y++)
		for (int x = 0; x < 20; x++) {
			Swiat1.Ustaw_Komorke(Fabryka_Komorek::Nowa_Komorka(0, 0), x, y);
		}

	/*
	 * Szybowiec i ropucha.
	 */

	Swiat1.Ustaw_Komorke(Fabryka_Komorek::Nowa_Komorka(0, 1), 3, 7);
	Swiat1.Ustaw_Komorke(Fabryka_Komorek::Nowa_Komorka(0, 1), 4, 7);
	Swiat1.Ustaw_Komorke(Fabryka_Komorek::Nowa_Komorka(0, 1), 5, 7);
	Swiat1.Ustaw_Komorke(Fabryka_Komorek::Nowa_Komorka(0, 1), 4, 8);
	Swiat1.Ustaw_Komorke(Fabryka_Komorek::Nowa_Komorka(0, 1), 5, 8);
	Swiat1.Ustaw_Komorke(Fabryka_Komorek::Nowa_Komorka(0, 1), 6, 8);

	Swiat1.Ustaw_Komorke(Fabryka_Komorek::Nowa_Komorka(0, 1), 10, 10);
	Swiat1.Ustaw_Komorke(Fabryka_Komorek::Nowa_Komorka(0, 1), 11, 10);
	Swiat1.Ustaw_Komorke(Fabryka_Komorek::Nowa_Komorka(0, 1), 12, 10);
	Swiat1.Ustaw_Komorke(Fabryka_Komorek::Nowa_Komorka(0, 1), 12, 11);
	Swiat1.Ustaw_Komorke(Fabryka_Komorek::Nowa_Komorka(0, 1), 11, 12);

	Wyswietl(&Swiat1);

#ifdef LINUX
	/*
	 * Testy wydajno¶ci
	 *
	 */
	{
		struct timeval tv, tv2;
		gettimeofday(&tv, 0);
		Swiat1.generacja();
		gettimeofday(&tv2, 0);
		printf("%ld mikrosekund\n", 1000000*(tv2.tv_sec - tv.tv_sec) + (tv2.tv_usec - tv.tv_usec));
	}
	Wyswietl(&Swiat1);

	{
		struct timeval tv, tv2;
		gettimeofday(&tv, 0);
		Swiat1.generacja();
		gettimeofday(&tv2, 0);
		printf("%ld mikrosekund\n", 1000000*(tv2.tv_sec - tv.tv_sec) + (tv2.tv_usec - tv.tv_usec));
	}
	Wyswietl(&Swiat1);

	{
		struct timeval tv, tv2;
		gettimeofday(&tv, 0);
		Swiat1.generacja();
		gettimeofday(&tv2, 0);
		printf("%ld mikrosekund\n", 1000000*(tv2.tv_sec - tv.tv_sec) + (tv2.tv_usec - tv.tv_usec));
	}
	Wyswietl(&Swiat1);

	{
		struct timeval tv, tv2;
		gettimeofday(&tv, 0);
		Swiat1.generacja();
		gettimeofday(&tv2, 0);
		printf("%ld mikrosekund\n", 1000000*(tv2.tv_sec - tv.tv_sec) + (tv2.tv_usec - tv.tv_usec));
	}
	Wyswietl(&Swiat1);
#endif

	return 0;
}

