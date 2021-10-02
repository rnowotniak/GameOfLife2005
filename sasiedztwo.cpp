/*
 * Copyright (C) 2004,2005   Robert Nowotniak <robercik@stud.ics.p.lodz.pl>
 * Copyright (C) 2004,2005   Micha³ Ostrowski <mostrow@stud.ics.p.lodz.pl>
 *
 */
#include "life.h"
#include "sasiedztwo.h"
#include "tablica_pol.h"
#include "pole.h"

Sasiedztwo_Neumanna::Sasiedztwo_Neumanna()
{
	N = S = E = W = 0;
}


Sasiedztwo_Moora::Sasiedztwo_Moora()
	: Sasiedztwo_Neumanna()
{
	NE = NW = SE = SW = 0;
}


Sasiedztwo_Neumanna::
Sasiedztwo_Neumanna(Tablica_Pol *T, int x, int y)
{
	Pole *p;

	N = (p = (*T)(x, y + 1)) ? p->komorka : 0;
	S = (p = (*T)(x, y - 1)) ? p->komorka : 0;
	E = (p = (*T)(x + 1, y)) ? p->komorka : 0;
	W = (p = (*T)(x - 1, y)) ? p->komorka : 0;
}


Sasiedztwo_Moora::
Sasiedztwo_Moora(Tablica_Pol *T, int x, int y)
	: Sasiedztwo_Neumanna(T, x, y)
{
	Pole *p;

	NE = (p = (*T)(x + 1, y + 1)) ? p->komorka : 0;
	NW = (p = (*T)(x - 1, y + 1)) ? p->komorka : 0;
	SE = (p = (*T)(x + 1, y - 1)) ? p->komorka : 0;
	SW = (p = (*T)(x - 1, y - 1)) ? p->komorka : 0;
}

