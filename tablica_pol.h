/*
 * Copyright (C) 2004,2005   Robert Nowotniak <robercik@stud.ics.p.lodz.pl>
 * Copyright (C) 2004,2005   Micha³ Ostrowski <mostrow@stud.ics.p.lodz.pl>
 *
 */
#ifndef __HAVE_TABLICA_POL_H
#define __HAVE_TABLICA_POL_H 1

#include <vector>
#include "life.h"
#include "pole.h"

class Tablica_Pol  {
	private:
		typedef std::vector<std::vector<Pole> > Wektor_Pol;
		Wektor_Pol tab;
	public:

		Tablica_Pol(int szerokosc, int wysokosc)
			: tab(std::vector<std::vector<Pole> >(szerokosc, std::vector<Pole>(wysokosc, Pole())))
			{ }
		Pole* operator()(int x, int y);
		int podaj_szerokosc();
		int podaj_wysokosc();
};


inline Pole* Tablica_Pol::operator()(int x, int y)
{
	if (x < 0 || x >= podaj_szerokosc())
		return 0;
	if (y < 0 || y >= podaj_wysokosc())
		return 0;

	return &tab[x][y];
}

inline int
Tablica_Pol::
podaj_szerokosc()
{
	return tab.size();
}


inline int
Tablica_Pol::
podaj_wysokosc()
{
	return tab[0].size();
}



#endif /* __HAVE_TABLICA_POL_H */
