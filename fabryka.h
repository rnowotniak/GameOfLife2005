/*
 * Copyright (C) 2004,2005   Robert Nowotniak <robercik@stud.ics.p.lodz.pl>
 * Copyright (C) 2004,2005   Micha³ Ostrowski <mostrow@stud.ics.p.lodz.pl>
 *
 */
#ifndef __HAVE_FABRYKA_H
#define __HAVE_FABRYKA_H 1

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include "life.h"
#include "komorka.h"
#ifdef HAVE_FLTK
#include <FL/Fl.H>
#endif

#ifdef LINUX
#include <dlfcn.h>
#else
#ifdef WIN32
#include <windows.h>
#endif
#endif

class Warunki_Srodowiska;

typedef std::vector<std::string> Wektor_String;
typedef std::vector<int> Wektor_Int;

class Fabryka_Komorek  {
	private:
		typedef std::set<Komorka> Zbior_Komorek;
		static Zbior_Komorek pula;

	public:
		static void Nowy_Rodzaj_Komorki(int typ, Komorka::funkcja_przejscia funkcja);

		static const Komorka* Nowa_Komorka(int typ, int stan);
		static const Komorka* Podaj_Komorke(int typ);

		static Wektor_Int Podaj_Typy();


		static void Zmien_Parametry(int typ, std::string nazwa);
		static void Zmien_Parametry(int typ, std::string modul, Komorka::funkcja_przejscia f);
#ifdef HAVE_FLTK
		static void Zmien_Parametry(int typ, Fl_Color kolor);
#endif

		static void Wyczysc_Pule();
};


class Fabryka_Warunkow_Srodowiska  {
	private:
		typedef std::set<Warunki_Srodowiska> Zbior_Warunkow_Srodowiska;
		static Zbior_Warunkow_Srodowiska pula;

	public:
		static const Warunki_Srodowiska* Nowe_Warunki(std::string N, double w = 0, double o = 0, double t = 0
#ifdef HAVE_FLTK
				, Fl_Color k = FL_DARK_YELLOW
#endif
				);

		static void Zmien_Parametry(std::string N, double w, double o, double t
#ifdef HAVE_FLTK
				, Fl_Color k = FL_DARK_YELLOW
#endif
				);


		static Wektor_String Podaj_Nazwy();

		static void Usun_Warunki(std::string N);
		static void Wyczysc_Pule();
};


class Fabryka_Funkcji {
	public:
		/*
		 * ("Nazwa pliku modu³u", (uchtyw biblioteki, wska¼nik na funkcjê przej¶cia))
		 */
#ifdef LINUX
		typedef std::map<std::string, std::pair<void*, Komorka::funkcja_przejscia> > Tabela_Modulow;
#else
#ifdef WIN32
		typedef std::map<std::string, std::pair<HINSTANCE, Komorka::funkcja_przejscia> > Tabela_Modulow;
#endif
#endif

	private:
		static Tabela_Modulow pula;

	public:
		static Komorka::funkcja_przejscia Zaladuj_Funkcje(std::string modul);
		static void Wyczysc_Pule();
};



#endif /* __HAVE_FABRYKA_H */
