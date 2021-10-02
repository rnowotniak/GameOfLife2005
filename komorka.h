/*
 * Copyright (C) 2004,2005   Robert Nowotniak <robercik@stud.ics.p.lodz.pl>
 * Copyright (C) 2004,2005   Micha³ Ostrowski <mostrow@stud.ics.p.lodz.pl>
 *
 */
#ifndef __HAVE_KOMORKA_H
#define __HAVE_KOMORKA_H 1

#include <vector>
#include <string>
#ifdef HAVE_FLTK
#include <FL/Enumerations.H>
#endif
#include "life.h"

class Sasiedztwo_Moora;
class Warunki_Srodowiska;


class Opis_Stanu  {
#ifdef HAVE_FLTK
	Fl_Color _kolor;
#endif
	std::string _nazwa;

	public:
#ifdef HAVE_FLTK
		Opis_Stanu(std::string n, Fl_Color k = FL_WHITE)
			: _nazwa(n), _kolor(k)  { }
#else
		Opis_Stanu(std::string n)
			: _nazwa(n)  { }
#endif
	
		std::string nazwa() const
			{return _nazwa;}
		std::string nazwa(std::string N)
			{return (_nazwa = N);}

#ifdef HAVE_FLTK
		Fl_Color kolor() const
			{return _kolor;}
		Fl_Color kolor(Fl_Color k)
			{return (_kolor = k);}
#endif
};

extern std::vector<Opis_Stanu> Opisy_Stanow;

class Komorka  {
	public:
		typedef int (*funkcja_przejscia)(const Warunki_Srodowiska *W, const Sasiedztwo_Moora *S, int stan);

	private:
		const int stan;
		const int typ;
		mutable funkcja_przejscia _funkcja;
		mutable std::string _nazwa;
		mutable std::string _modul;

#ifdef HAVE_FLTK
		mutable Fl_Color _kolor;
#endif

	public:
		Komorka(
				int t,
				funkcja_przejscia f,
				int s = 0
#ifdef HAVE_FLTK
				, Fl_Color k = FL_WHITE
#endif
				);


		int podaj_stan() const;
		int podaj_typ() const;

		std::string nazwa() const;
		funkcja_przejscia funkcja() const;
		std::string modul() const;

		/*
		 * Funkcje zmieniaj± atrybuty, ale zachowuj± sta³o¶æ logiczn±
		 * obiektu. Relacja porz±dkuj±ca w zbiorze obiektów nie opiera
		 * siê na tych atrybutach, które s± tu zmienione.
		 */
		void nazwa(std::string n) const;
		void funkcja(funkcja_przejscia f) const;
		void modul(std::string m) const;

#ifdef HAVE_FLTK
		Fl_Color kolor() const;
		void kolor(Fl_Color k) const; // Zachowuje sta³o¶æ logiczn±
#endif

		bool operator==(const Komorka & K2) const;
		bool operator<(const Komorka & K2) const;
};



/*
 * Definicje funkcji inline
 */


inline int
Komorka::
podaj_typ() const
{
	return typ;
}


inline int
Komorka::
podaj_stan() const
{
	return stan;
}

#ifdef HAVE_FLTK
inline
Fl_Color
Komorka::
kolor() const
{
	return _kolor;
}
#endif



inline Komorka::funkcja_przejscia
Komorka::
funkcja() const
{
	return _funkcja;
}

inline std::string
Komorka::
nazwa() const
{
	return _nazwa;
}


inline std::string
Komorka::
modul() const
{
	return _modul;
}


inline void
Komorka::
funkcja(funkcja_przejscia f) const
{
	_funkcja = f;
}

inline void
Komorka::
nazwa(std::string n) const
{
	_nazwa = n;
}

inline void
Komorka::
modul(std::string n) const
{
	_modul = n;
}

#ifdef HAVE_FLTK
inline void
Komorka::
kolor(Fl_Color k) const
{
	_kolor = k;
}
#endif

inline bool Komorka::
operator==(const Komorka & K2) const
{
	return typ == K2.typ && stan == K2.stan;
}

inline bool Komorka::
operator<(const Komorka & K2) const
{
	return typ < K2.typ ? true : stan < K2.stan;
}



#endif /* __HAVE_KOMORKA_H */
