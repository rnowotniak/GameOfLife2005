/*
 * Copyright (C) 2004,2005   Robert Nowotniak <robercik@stud.ics.p.lodz.pl>
 * Copyright (C) 2004,2005   Micha³ Ostrowski <mostrow@stud.ics.p.lodz.pl>
 *
 */
#ifndef __HAVE_SRODOWISKO_H
#define __HAVE_SRODOWISKO_H 1

#include <string>
#ifdef HAVE_FLTK
#include <FL/Enumerations.H>
#endif
#include "life.h"
#include "fabryka.h"

class Warunki_Srodowiska  {
	mutable double _wilgotnosc;
	mutable double _oswietlenie;
	mutable double _temperatura;
#ifdef HAVE_FLTK
	mutable Fl_Color _kolor;
#endif

	public:
		const std::string nazwa;

		double wilgotnosc() const;
		double oswietlenie() const;
		double temperatura() const;

		Warunki_Srodowiska(std::string N, double w = 0, double o = 0, double t = 0
#ifdef HAVE_FLTK
				, Fl_Color k = FL_DARK_YELLOW
#endif
				);

		Warunki_Srodowiska();

#ifdef HAVE_FLTK
		int kolor() const;
#endif

		friend void Fabryka_Warunkow_Srodowiska::
			Zmien_Parametry(std::string N, double w, double o, double t
#ifdef HAVE_FLTK
				, Fl_Color k
#endif
				);

		bool operator==(const Warunki_Srodowiska &E) const;
		bool operator<(const Warunki_Srodowiska &E) const;
};

inline
double
Warunki_Srodowiska::
wilgotnosc() const
{
	return _wilgotnosc;
}

inline
double
Warunki_Srodowiska::
oswietlenie() const
{
	return _oswietlenie;
}

inline
double
Warunki_Srodowiska::
temperatura() const
{
	return _temperatura;
}


#ifdef HAVE_FLTK
inline
int
Warunki_Srodowiska::
kolor() const
{
	return _kolor;
}
#endif



inline Warunki_Srodowiska::
Warunki_Srodowiska(std::string N, double w, double o, double t
#ifdef HAVE_FLTK
	, Fl_Color k
#endif
)
	: nazwa(N), _wilgotnosc(w), _oswietlenie(o), _temperatura(t)
#ifdef HAVE_FLTK
	, _kolor(k)
#endif
{ }

inline Warunki_Srodowiska::
Warunki_Srodowiska()
	: nazwa("Warunki domyslne"), _wilgotnosc(0), _oswietlenie(0), _temperatura(0)
#ifdef HAVE_FLTK
	, _kolor(FL_DARK_YELLOW)
#endif
{ }

inline bool
Warunki_Srodowiska::
operator==(const Warunki_Srodowiska &E) const
{
	return nazwa == E.nazwa;
}

inline bool
Warunki_Srodowiska::
operator<(const Warunki_Srodowiska &E) const
{
	return nazwa < E.nazwa;
}

#endif /* __HAVE_SRODOWISKO_H */
