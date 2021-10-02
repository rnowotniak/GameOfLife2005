/*
 * Copyright (C) 2004,2005   Robert Nowotniak <robercik@stud.ics.p.lodz.pl>
 * Copyright (C) 2004,2005   Micha³ Ostrowski <mostrow@stud.ics.p.lodz.pl>
 *
 */
#include <cstdio>
#include <stdint.h>
#include "life.h"
#include "ekosystem.h"
#include "sasiedztwo.h"
#include "fabryka.h"
#include "pole.h"
#include "srodowisko.h"

Ekosystem::Ekosystem(int szerokosc, int wysokosc)
{
	tablica = new Tablica_Pol(szerokosc, wysokosc);
	bufor = new Tablica_Pol(szerokosc, wysokosc);

	srand(time(0));
	opcje.losowe_komorki(false);

	/*
	 * Standardowe parametry stanów, jakie¶ domy¶lne kolorki.
	 */
#ifdef HAVE_FLTK
	Opisy_Stanow.push_back(Opis_Stanu("Komorka martwa", FL_BLACK));
	Opisy_Stanow.push_back(Opis_Stanu("Komorka zywa", FL_WHITE));
	Opisy_Stanow.push_back(Opis_Stanu("Stan numer 2", FL_RED));
	Opisy_Stanow.push_back(Opis_Stanu("Stan numer 3", FL_DARK_BLUE));
	Opisy_Stanow.push_back(Opis_Stanu("Stan numer 4", FL_DARK_CYAN));
	Opisy_Stanow.push_back(Opis_Stanu("Stan numer 5", FL_DARK_GREEN));
	Opisy_Stanow.push_back(Opis_Stanu("Stan numer 6", FL_DARK_MAGENTA));
	Opisy_Stanow.push_back(Opis_Stanu("Stan numer 7", FL_DARK_RED));
	Opisy_Stanow.push_back(Opis_Stanu("Stan numer 8", FL_DARK_YELLOW));
	Opisy_Stanow.push_back(Opis_Stanu("Stan numer 9", FL_BLUE));
#else
	Opisy_Stanow.push_back(Opis_Stanu("Komorka martwa"));
	Opisy_Stanow.push_back(Opis_Stanu("Komorka zywa"));
	Opisy_Stanow.push_back(Opis_Stanu("Stan numer 2"));
	Opisy_Stanow.push_back(Opis_Stanu("Stan numer 3"));
	Opisy_Stanow.push_back(Opis_Stanu("Stan numer 4"));
	Opisy_Stanow.push_back(Opis_Stanu("Stan numer 5"));
	Opisy_Stanow.push_back(Opis_Stanu("Stan numer 6"));
	Opisy_Stanow.push_back(Opis_Stanu("Stan numer 7"));
	Opisy_Stanow.push_back(Opis_Stanu("Stan numer 8"));
	Opisy_Stanow.push_back(Opis_Stanu("Stan numer 9"));
#endif /* ! HAVE_FLTK */

}


Ekosystem::~Ekosystem()
{
	delete tablica;
	delete bufor;

	Opisy_Stanow.clear();
	Fabryka_Komorek::Wyczysc_Pule();
	Fabryka_Warunkow_Srodowiska::Wyczysc_Pule();
	Fabryka_Funkcji::Wyczysc_Pule();
}


void
Ekosystem::
zamien_tablice() 
{
	Tablica_Pol *tmp = tablica;

	tablica = bufor;
	bufor = tmp;
}



void
Ekosystem::
Ustaw_Srodowisko(const Warunki_Srodowiska *E, int x, int y)
{
	Pole *p;

	if ((p = (*tablica)(x, y)))
		p->Ustaw_Srodowisko(E);
	if ((p = (*bufor)(x, y)))
		p->Ustaw_Srodowisko(E);
}


void
Ekosystem::generacja()
{
	int stan, typ;
	Sasiedztwo_Moora sasiedztwo;
	Pole *p;

	int wysokosc = tablica->podaj_wysokosc();
	int szerokosc = tablica->podaj_szerokosc();

	for (int y = 0; y < wysokosc; y++)
		for (int x = 0; x < szerokosc; x++) {
			p = (*tablica)(x, y);

			if (! p->komorka) {
				/*
				 * Danie szansy losowemu rodzajowi koórki na powstanie na tym polu.
				 */
				if (opcje.losowe_komorki()) {
					Wektor_Int typy = Fabryka_Komorek::Podaj_Typy();

					if (! typy.size())
						continue;

					p->komorka = Fabryka_Komorek::Podaj_Komorke(typy[rand() % typy.size()]);

					sasiedztwo = Sasiedztwo_Moora(tablica, x, y);
					stan = p->cykl(&sasiedztwo);
					if (stan)
						(*bufor)(x, y)->komorka = p->komorka;
					else
						p->komorka = 0;
				}
				continue;
			}

			sasiedztwo = Sasiedztwo_Moora(tablica, x, y);
			stan = p->cykl(&sasiedztwo);

			if (stan != p->komorka->podaj_stan()) {
				typ = p->komorka->podaj_typ();
				(*bufor)(x, y)->komorka = Fabryka_Komorek::Nowa_Komorka(typ, stan);
			} else
				(*bufor)(x, y)->komorka = p->komorka;
		}

	zamien_tablice();
}


void
Ekosystem::
Usmierc_Komorki()
{
	int w = tablica->podaj_szerokosc();
	int h = tablica->podaj_wysokosc();

	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			Ustaw_Stan(0, x, y);
}


void
Ekosystem::
Wypelnij_Caly(const Komorka *K)
{
	int w = tablica->podaj_szerokosc();
	int h = tablica->podaj_wysokosc();
	
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			Ustaw_Komorke(K, x, y);
}


void
Ekosystem::
Wczytaj_LIF(FILE *Plik, int wzg_x, int wzg_y, int stan)
{
	if (!Plik)
		return;

	/*
	 * Interesuj± nas tylko linie wzglêdnego po³o¿enia #P
	 * oraz liniê z informacjami o stanie komórek
	 */


	int c;
	int px = 0, py = 0;
	bool sa_juz_wspolrzedne = false;
	std::string Linia;

	for (;;) {
		Linia = "";

		while ((c = fgetc(Plik)) != EOF && c != '\n')
			Linia.append(1, char(c));

		if (c == EOF)
			return;

		if (Linia[Linia.length() - 1] == '\r')
			Linia.erase(Linia.length() - 1);

		if (! Linia.compare(0, 4, "#END"))
			return;

		/*
		 * To nas nie interesuje
		 */
		if (! Linia.compare(0, 6, "#Life "))
			continue;

		if (! Linia.compare(0, 3, "#D "))
			continue;
		if (! Linia.compare(0, 3, "#C "))
			continue;

		if (! Linia.compare(0, 2, "#R"))
			continue;
		if (! Linia.compare(0, 2, "#N"))
			continue;

		/*
		 * Wzglêdne po³o¿enie bloku
		 */
		if (! Linia.compare(0, 3, "#P ")) {
			if (sscanf(Linia.c_str() + 3, "%d %d", &px, &py) == 2)
				sa_juz_wspolrzedne = true;
			continue;
		}

		if (! sa_juz_wspolrzedne)
			/* b³±d semantyczny, no ale wczytujmy dalej */
			continue;

		if (Linia.find_first_not_of(".*0123456789") != std::string::npos)
			/* w tej linii b³±d sk³adni, no ale wczytujmy dalej */
			continue;

		for (int n = 0; n < Linia.length(); n++) {
			if (Linia[n] == '*')
				Ustaw_Stan(stan, wzg_x + px + n, wzg_y + py);
			else if (Linia[n] == '.')
				Ustaw_Stan(0, wzg_x + px + n, wzg_y + py);
			else /* Moze juz byc tylko cyfra numeru stanu */
				Ustaw_Stan(Linia[n] - '0', wzg_x + px + n, wzg_y + py);
		}

		py++;
	}

}


void
Ekosystem::
Wczytaj(FILE *Plik)
{
	if (! Plik)
		return;


	std::string Linia;
	int c;
	
	// Sekcje w pliku ekosystemu
	enum {
		global, stany, warunki, rodzaje,
		lif, mapa_warunkow, mapa_rodzajow
	} faza = global;

	uint32_t kolor;
	int stan, rodzaj;
	int l, szer, wys;
	int nr_warunkow = 0, nr_rodzaju = 0;
	float w, o, t;
	const char *nazwa;
	char modul[PATH_MAXLEN];
	std::map<int, const Warunki_Srodowiska*> Kolejnosc_Warunkow;

	for (;;) {
		Linia = "";
		while ((c = fgetc(Plik)) != EOF && c != '\n')
			Linia.append(1, char(c));

		if (c == EOF)
			return;
		if (Linia[Linia.length() - 1] == '\r')
			Linia.erase(Linia.length() - 1);

		if (Linia.empty()) {
			faza = global;
			continue;
		}
		else if (! Linia.compare(0, 5, "Stany")) {
			faza = stany;
			continue;
		}
		else if (! Linia.compare(0, 7, "Warunki")) {
			faza = warunki;
			continue;
		}
		else if (! Linia.compare(0, 7, "Rodzaje")) {
			faza = rodzaje;
			continue;
		}
		else if (! Linia.compare(0, 6, "#Life ")) {
			Wczytaj_LIF(Plik,
					tablica->podaj_szerokosc() / 2,
					tablica->podaj_wysokosc() / 2,
					1);
			continue;
		}
		else if (! Linia.compare(0, 13, "Mapa Warunkow")) {
			faza = mapa_warunkow;
		}
		else if (! Linia.compare(0, 13, "Mapa Rodzajow")) {
			faza = mapa_rodzajow;
		}

		switch (faza) {
			case global:
				if (! Linia.compare(0, 8, "Rozmiar ")) {
					sscanf(Linia.c_str(), "Rozmiar %d %d", &szer, &wys);
					delete tablica;
					delete bufor;
					tablica = new Tablica_Pol(szer, wys);
					bufor = new Tablica_Pol(szer, wys);
				}
				break;
			case stany:
				sscanf(Linia.c_str(), "%u %u %n", &stan, &kolor, &l);
				nazwa = &Linia.c_str()[l];
				if (stan >= Opisy_Stanow.size())
					Opisy_Stanow.resize(stan + 1, Opis_Stanu(std::string()));
				Opisy_Stanow[stan].nazwa(nazwa);
#ifdef HAVE_FLTK
				Opisy_Stanow[stan].kolor(Fl_Color(kolor));
#endif
				break;
			case warunki:
				sscanf(Linia.c_str(), "%f %f %f %u %n",
						&w, &o, &t, &kolor, &l);
				nazwa = &Linia.c_str()[l];

				Kolejnosc_Warunkow[nr_warunkow++] =
#ifdef HAVE_FLTK
					Fabryka_Warunkow_Srodowiska::Nowe_Warunki(nazwa, w, o, t, Fl_Color(kolor));
#else
					Fabryka_Warunkow_Srodowiska::Nowe_Warunki(nazwa, w, o, t);
#endif
				break;
			case rodzaje:
				sscanf(Linia.c_str(), "%u %u %s %n", &rodzaj, &kolor, modul, &l);
				nazwa = &Linia.c_str()[l];
				
#ifdef LINUX
				if (strlen(modul) > 4 && ! strcasecmp(&modul[strlen(modul) - 4], ".dll"))
					strncpy(&modul[strlen(modul) - 4], ".so", 4);
#else
#ifdef WIN32
				if (strlen(modul) > 3 && ! strcasecmp(&modul[strlen(modul) - 3], ".so"))
					strncpy(&modul[strlen(modul) - 3], ".dll", 5);
#endif
#endif

				Fabryka_Komorek::Nowy_Rodzaj_Komorki(rodzaj, 0);
				Fabryka_Komorek::Zmien_Parametry(rodzaj, modul, Fabryka_Funkcji::Zaladuj_Funkcje(modul));
				Fabryka_Komorek::Zmien_Parametry(rodzaj, nazwa);
#ifdef HAVE_FLTK
				Fabryka_Komorek::Zmien_Parametry(rodzaj, Fl_Color(kolor));
#endif
				break;
			case mapa_warunkow:
				for (int y = 0; y < tablica->podaj_wysokosc(); y++)
					for (int x = 0; x < tablica->podaj_wysokosc(); x++) {
						fscanf(Plik, "%u", &nr_warunkow);
						Ustaw_Srodowisko(Kolejnosc_Warunkow[nr_warunkow], x, y);
					}
				faza = global;
				break;
			case mapa_rodzajow:
				for (int y = 0; y < tablica->podaj_wysokosc(); y++)
					for (int x = 0; x < tablica->podaj_wysokosc(); x++) {
						fscanf(Plik, "%d", &nr_rodzaju);
						if (nr_rodzaju > 0)
							Ustaw_Komorke(
									Fabryka_Komorek::Nowa_Komorka(nr_rodzaju, 0),
									x, y);
					}
				faza = global;
				break;
		}
	}
}


void
Ekosystem::
Zapisz(FILE *Plik) const
{
	if (! Plik)
		return;

	// Wielkosæ tablicy
	fprintf(Plik, "Rozmiar %d %d\r\n\r\n",
			tablica->podaj_szerokosc(),
			tablica->podaj_wysokosc());

	// Stany - numery, kolory, opisy
	fprintf(Plik, "Stany\r\n");
	for (int n = 0; n < Opisy_Stanow.size(); n++)
		if (! Opisy_Stanow[n].nazwa().empty())
			fprintf(Plik, "   %u %u %s\r\n",
					n, Opisy_Stanow[n].kolor(), Opisy_Stanow[n].nazwa().c_str());

	// Warunki ¶rodowiska - parametry, kolory, nazwy
	std::map<std::string, int> Warunki_Map;
	fprintf(Plik, "Warunki\r\n");
	Wektor_String nazwy_warunkow = Fabryka_Warunkow_Srodowiska::Podaj_Nazwy();
	for (int n = 0; n < nazwy_warunkow.size(); n++) {
		const Warunki_Srodowiska *W = Fabryka_Warunkow_Srodowiska::Nowe_Warunki(nazwy_warunkow[n]);

		Warunki_Map[W->nazwa] = n;

		fprintf(Plik, "   %f %f %f %u %s\r\n",
				W->wilgotnosc(),
				W->oswietlenie(),
				W->temperatura(),
				W->kolor(),
				W->nazwa.c_str());
	}

	// Rodzaje komórek - numery, kolory, modu³y, nazwy
	fprintf(Plik, "Rodzaje\r\n");
	Wektor_Int Typy_Komorek = Fabryka_Komorek::Podaj_Typy();
	for ( Wektor_Int::iterator i = Typy_Komorek.begin();
			i != Typy_Komorek.end();
			i++) {
		const Komorka *K = Fabryka_Komorek::Podaj_Komorke(*i);
		fprintf(Plik, "   %u %u %s %s\r\n",
				K->podaj_typ(),
				K->kolor(),
				K->modul().c_str(),
				K->nazwa().c_str());
	}

	fprintf(Plik, "\r\n");

	// Mapa z Warunkami ¶rodowiska
	fprintf(Plik, "Mapa Warunkow\r\n");
	const Warunki_Srodowiska *W;
	for (int y = 0; y < tablica->podaj_wysokosc(); y++) {
		fprintf(Plik, "   ");
		for (int x = 0; x < tablica->podaj_szerokosc(); x++) {
			if ((W = Podaj_Srodowisko(x, y)))
				fprintf(Plik, " %u", Warunki_Map[W->nazwa]);
		}
		fprintf(Plik, "\r\n");
	}
	fprintf(Plik, "\r\n");

	// Mapa z Rodzajami Komórek
	fprintf(Plik, "Mapa Rodzajow\r\n");
	const Komorka *K;
	for (int y = 0; y < tablica->podaj_wysokosc(); y++) {
		fprintf(Plik, "   ");
		for (int x = 0; x < tablica->podaj_szerokosc(); x++) {
			if (! (K = (*tablica)(x,y)->komorka))
				fprintf(Plik, " -1");
			else
				fprintf(Plik, " %u", K->podaj_typ());
		}
		fprintf(Plik, "\r\n");
	}
	fprintf(Plik, "\r\n");

	// Reszta to ju¿ tylko LIF
	Zapisz_LIF(Plik, tablica->podaj_szerokosc() / 2, tablica->podaj_wysokosc() / 2);
	fprintf(Plik, "\r\n");

}

void
Ekosystem::
Zapisz_LIF(FILE *Plik, int wzg_x, int wzg_y) const
{
	if (! Plik)
		return;

	fprintf(Plik, "#Life 1.05\r\n");
	fprintf(Plik, "#D\r\n");
	fprintf(Plik, "#D Plik wygenerowany przez Game Of Life Reactivated\r\n");
	fprintf(Plik, "#D\r\n");

	/*
	 * W plikach formatu LIF tablica jest dzielona na bloki
	 */

	const int ROZMIAR_BLOKU = 8;
	char Obszar[ROZMIAR_BLOKU][ROZMIAR_BLOKU];

	// Do porównywania
	const char Pusta_Linia[ROZMIAR_BLOKU] =  { '\0' };
	bool pusty_blok;

	for (int by = 0; by < tablica->podaj_wysokosc(); by += ROZMIAR_BLOKU)
		for (int bx = 0; bx < tablica->podaj_szerokosc(); bx += ROZMIAR_BLOKU) {

			pusty_blok = true;
			for (int y = 0; y < ROZMIAR_BLOKU; y++)
				for (int x = 0; x < ROZMIAR_BLOKU; x++)
					if ((Obszar[y][x] = Podaj_Stan(x + bx, y + by)))
						pusty_blok = false;

			if (pusty_blok)
				continue;
			fprintf(Plik, "#P %d %d\r\n", bx - wzg_x, by - wzg_y);

			for (int y = 0; y < ROZMIAR_BLOKU; y++) {
				if (! memcmp(Obszar[y], Pusta_Linia, ROZMIAR_BLOKU))
					fprintf(Plik, ".");
				else
					for (int x = 0; x < ROZMIAR_BLOKU; x++)
						fprintf(Plik, "%c", Obszar[y][x] + '0');
				fprintf(Plik, "\r\n");
			}
		}
}

