/*
 * Copyright (C) 2004,2005   Robert Nowotniak <robercik@stud.ics.p.lodz.pl>
 * Copyright (C) 2004,2005   Micha³ Ostrowski <mostrow@stud.ics.p.lodz.pl>
 *
 */
#include "life.h"
#include "komorka.h"


#ifdef HAVE_FLTK
Komorka::
Komorka(int t, funkcja_przejscia f, int s , Fl_Color k)
	: typ(t), stan(s), _modul(""), _nazwa(""), _kolor(k)
#else
Komorka::
Komorka(int t, funkcja_przejscia f, int s)
	: typ(t), stan(s), _modul(""), _nazwa("")
#endif
{
	this->_funkcja = f;
}

std::vector<Opis_Stanu> Opisy_Stanow;

