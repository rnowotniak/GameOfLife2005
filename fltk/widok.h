/*
 * Copyright (C) 2004,2005   Robert Nowotniak <robercik@stud.ics.p.lodz.pl>
 * Copyright (C) 2004,2005   Micha³ Ostrowski <mostrow@stud.ics.p.lodz.pl>
 *
 */
#ifndef __HAVE_WIDOK_H
#define __HAVE_WIDOK_H 1

#include <cmath>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <FL/fl_ask.H>
#include "ekosystem.h"
#include "tablica_pol.h"
#include "srodowisko.h"

class Ekosystem;

class Widok : public Fl_Box  {
	public:
		enum Rodzaj_Widoku {Srodowisko, Stany, Typy_Komorek};

	private:
		/*
		 * Po³o¿enie centralnej w aktualnym widoku komórki
		 * wzglêdem ¶rodka tablicy w Ekosystemie
		 */
		int przesuniecie_x;
		int przesuniecie_y;

		float powiekszenie;
		int promien_modyfikacji;
		int wzgledny_promien_modyfikacji;

		/*
		 * Pomocnicze zmienne, u¿ywane w algorytmie wy¶wietlania
		 */
		int ilosc_x, ilosc_y;
		int krok_x, krok_y;
		int px, py;

		void przelicz_wspolczynniki();


		Rodzaj_Widoku maska;
		Ekosystem *ekosystem;

	protected:
		void draw();
		int handle(int event);

	public:
		Widok(int x, int y, int w, int h, const char *label = 0);
		~Widok();


		void Pokazuj_Ekosystem(Ekosystem *E);
		void Ustaw_Maske(Rodzaj_Widoku m);
		Rodzaj_Widoku Podaj_Maske() const;
		Ekosystem* Podaj_Ekosystem() const;

		void Ustaw_Promien_Modyfikacji(int p);

		void powieksz();
		void pomniejsz();
		void przesun_w_lewo();
		void przesun_w_prawo();
		void przesun_w_gore();
		void przesun_w_dol();

		void przywroc();
};



#endif /* __HAVE_WIDOK_H */
