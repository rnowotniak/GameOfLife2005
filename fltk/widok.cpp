/*
 * Copyright (C) 2004,2005   Robert Nowotniak <robercik@stud.ics.p.lodz.pl>
 * Copyright (C) 2004,2005   Micha³ Ostrowski <mostrow@stud.ics.p.lodz.pl>
 *
 */
#include <FL/Fl_Choice.H>
#include <cassert>
#include "widok.h"


Widok::
Widok(int x, int y, int w, int h, const char *label)
	: Fl_Box(x, y, w, h, label)
{
	przesuniecie_x = 0;
	przesuniecie_y = 0;
	powiekszenie = 1;
	promien_modyfikacji = 0;
	wzgledny_promien_modyfikacji = 0;
	ekosystem = 0;
	maska = Stany;

	krok_x = 0;
	krok_y = 0;
	ilosc_x = 0;
	ilosc_y = 0;
	px = 0;
	py = 0;

	przelicz_wspolczynniki();
}


Widok::
~Widok()
{
	if (ekosystem)
		delete ekosystem;
}

void
Widok::
powieksz()
{
	powiekszenie++;
	przelicz_wspolczynniki();
}

void
Widok::
pomniejsz()
{
	if (powiekszenie < 2) {
		fl_beep();
		return;
	}
	powiekszenie--;
	przelicz_wspolczynniki();
}

/*
 * Przesuwanie jest o 1/10 aktualnie widzianego obszaru
 */

void
Widok::
przesun_w_lewo()
{
	if (ekosystem) {
		przesuniecie_x -= int(ceil(1.0 * ekosystem->podaj_tablice()->podaj_szerokosc() / 10.0 / powiekszenie));
		przelicz_wspolczynniki();
	}
}

void
Widok::
przesun_w_prawo()
{
	if (ekosystem) {
		przesuniecie_x += int(ceil(1.0 * ekosystem->podaj_tablice()->podaj_szerokosc() / 10.0 / powiekszenie));
		przelicz_wspolczynniki();
	}
}

void
Widok::
przesun_w_gore()
{
	if (ekosystem) {
		przesuniecie_y -= int(ceil(1.0 * ekosystem->podaj_tablice()->podaj_wysokosc() / 10.0 / powiekszenie));
		przelicz_wspolczynniki();
	}
}

void
Widok::
przesun_w_dol()
{
	if (ekosystem) {
		przesuniecie_y += int(ceil(1.0 * ekosystem->podaj_tablice()->podaj_wysokosc() / 10.0 / powiekszenie));
		przelicz_wspolczynniki();
	}
}


/*
 * Powrot do poczatkowego pokazywania ca³o¶ci ekosystemu
 */
void Widok::
przywroc()
{
	if (ekosystem) {
		przesuniecie_x = ekosystem->podaj_tablice()->podaj_szerokosc() / 2;
		przesuniecie_y = ekosystem->podaj_tablice()->podaj_wysokosc() / 2;
		powiekszenie = 1;
		przelicz_wspolczynniki();
	}
}


void
Widok::
draw()
{
	Fl_Box::draw();

	if (!ekosystem)
		return;

	fl_push_clip(x(), y(), w() - 1, h() - 1);

	const Pole *p;
	const Komorka *k;
	const Warunki_Srodowiska *W;

	if (ilosc_x <= 20)  {
		/*
		 * Przy du¿ym powiêkszeniu (ma³o pól do pokazania)
		 * narysujemy kratkê pomocnicz±
		 */
		fl_color(FL_WHITE);
		for (int y = 0; y < ilosc_y; y++)
			fl_line(0, this->y() + 1 + y * krok_y, this->x() + w(), this->y() + 1 + y * krok_y);
		for (int x = 0; x < ilosc_x; x++)
			fl_line(this->x() + 1 + x * krok_x, 0, this->x() + 1 + x * krok_x, this->y() + h());
	}

	switch (maska) {
		case Srodowisko:
			for (int y = 0; y < ilosc_y; y++)
				for (int x = 0; x < ilosc_x; x++) {
					fl_color((W = ekosystem->Podaj_Srodowisko(x + px, y + py)) ? W->kolor() : FL_BLACK);
					fl_rectf(this->x() + 1 + x * krok_x, this->y() + 1 + y * krok_y, krok_x, krok_y);
				}
			break;

		case Stany:
			for (int y = 0; y < ilosc_y; y++)
				for (int x = 0; x < ilosc_x; x++)  {
					if (ekosystem->Podaj_Stan(x + px, y + py)) {
						fl_color(Opisy_Stanow[(*ekosystem->podaj_tablice())(x + px, y +py)->komorka->podaj_stan()].kolor());
						fl_rectf(this->x() + 1 + x * krok_x, this->y() + 1 + y * krok_y, krok_x, krok_y);
					}
				}
			break;

		case Typy_Komorek:
			for (int y = 0; y < ilosc_y; y++)
				for (int x = 0; x < ilosc_x; x++)
					if ((p = (*ekosystem->podaj_tablice())(x + px, y + py))
							&& p->komorka) {
						fl_color(p->komorka->kolor());
						fl_rectf(this->x() + 1 + x * krok_x, this->y() + 1 + y * krok_y, krok_x, krok_y);
					}
			break;
	}

	fl_pop_clip();
}


int
Widok::
handle(int event)
{
	switch (event) {
		case FL_PUSH:
			{
				/*
				 * Tutaj odbywa siê rysowanie komórkami/stanami/warunkami po obszarze Widoku
				 */

				if (!ekosystem) {
					fl_message("Najpierw musisz utworzyæ ekosystem, aby modyfikowaæ pola.");
					return 1;
				}

				/*
				 * Widok powinien otrzymywaæ w user_data wskazanie na listê wyboru!
				 */
				assert(user_data());

				const Fl_Menu_Item *wybor = ((Fl_Choice*)user_data())->mvalue();
				if (!wybor)
					return 1;

				/*
				 * Takie s± wspó³rzêdne w tablicy pól pola, na które klikn±³
				 * u¿ytkownik - bior±c pod uwagê aktualne powiêkszenie i przesuniêcie
				 */
				int x = (Fl::event_x() - this->x()) / krok_x + px;
				int y = (Fl::event_y() - this->y()) / krok_y + py;

				int stan;
				const Komorka *k;
				const Warunki_Srodowiska *W;

				switch (maska) {
					case Srodowisko:
						W = (const Warunki_Srodowiska*)(wybor->user_data());
						for (int n = -promien_modyfikacji; n <= promien_modyfikacji; n++)
							for (int m = -promien_modyfikacji; m <= promien_modyfikacji; m++)
								ekosystem->Ustaw_Srodowisko(W, x + n, y + m);
						break;

					case Stany:
						stan = (int)(wybor->user_data());
						for (int n = -promien_modyfikacji; n <= promien_modyfikacji; n++)
							for (int m = -promien_modyfikacji; m <= promien_modyfikacji; m++)
								ekosystem->Ustaw_Stan(stan, x + n, y + m);
						break;

					case Typy_Komorek:
						k = (const Komorka*)(wybor->user_data());
						for (int n = -promien_modyfikacji; n <= promien_modyfikacji; n++)
							for (int m = -promien_modyfikacji; m <= promien_modyfikacji; m++)
								ekosystem->Ustaw_Komorke(k, x + n, y + m);
						break;
				}

				redraw();

				return 1;
			}

		case FL_MOUSEWHEEL:
			if (Fl::event_dy() > 0)
				pomniejsz();
			else if (Fl::event_dy() < 0)
				powieksz();
			redraw();
			return 1;
		case FL_DRAG:
			return handle(FL_PUSH);
		case FL_ENTER:
			fl_cursor(FL_CURSOR_CROSS, FL_BLACK, FL_WHITE);
			return 1;
		case FL_LEAVE:
			fl_cursor(FL_CURSOR_DEFAULT, FL_BLACK, FL_WHITE);
			return 1;
		default:
			return Fl_Box::handle(event);
	}
}

void
Widok::
Ustaw_Promien_Modyfikacji(int p)
{
	wzgledny_promien_modyfikacji = p;
	przelicz_wspolczynniki();
}


void
Widok::
przelicz_wspolczynniki()
{
	if (!ekosystem)
		return;

	// Tyle pól jest do pokazywania
	ilosc_y = int(ceil(1.0 * ekosystem->podaj_tablice()->podaj_wysokosc() / powiekszenie));
	ilosc_x = int(ceil(1.0 * ekosystem->podaj_tablice()->podaj_szerokosc() / powiekszenie));

	// Tyle pikseli maj± boki pola
	krok_y = int(ceil(1.0 * h() / ilosc_y));
	krok_x = int(ceil(1.0 * w() / ilosc_x));

	px = przesuniecie_x - ilosc_x / 2;
	py = przesuniecie_y - ilosc_y / 2;

	promien_modyfikacji = wzgledny_promien_modyfikacji * ilosc_x / 16;
}


Widok::Rodzaj_Widoku
Widok::
Podaj_Maske() const
{
	return maska;
}


void
Widok::Pokazuj_Ekosystem(Ekosystem *E)
{
	if ((ekosystem = E))  {
		przesuniecie_x = ekosystem->podaj_tablice()->podaj_szerokosc() / 2;
		przesuniecie_y = ekosystem->podaj_tablice()->podaj_wysokosc() / 2;
		powiekszenie = 1;
		przelicz_wspolczynniki();
		redraw();
	}
}


Ekosystem*
Widok::
Podaj_Ekosystem() const
{
	return ekosystem;
}

void
Widok::
Ustaw_Maske(Rodzaj_Widoku m)
{
	maska = m;
}
