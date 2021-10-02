/*
 * Copyright (C) 2004,2005   Robert Nowotniak <robercik@stud.ics.p.lodz.pl>
 * Copyright (C) 2004,2005   Micha³ Ostrowski <mostrow@stud.ics.p.lodz.pl>
 *
 */
#ifndef __HAVE_COMMON_H
#define __HAVE_COMMON_H 1

#include "life.h"
#include "komorka.h"
#include "sasiedztwo.h"


inline int Zlicz_Sasiadow_W_Stanie(const Sasiedztwo_Moora *S, int stan)
{
	int Sasiedzi = 0;
	const Komorka *k;

	if ((k = S->Sasiad_Polnocny()) && k->podaj_stan() == stan)
		Sasiedzi++;
	if ((k = S->Sasiad_Poludniowy()) && k->podaj_stan() == stan)
		Sasiedzi++;
	if ((k = S->Sasiad_Zachodni()) && k->podaj_stan() == stan)
		Sasiedzi++;
	if ((k = S->Sasiad_Wschodni()) && k->podaj_stan() == stan)
		Sasiedzi++;
	if ((k = S->Sasiad_Polnocno_Zachodni()) && k->podaj_stan() == stan)
		Sasiedzi++;
	if ((k = S->Sasiad_Polnocno_Wschodni()) && k->podaj_stan() == stan)
		Sasiedzi++;
	if ((k = S->Sasiad_Poludniowo_Zachodni()) && k->podaj_stan() == stan)
		Sasiedzi++;
	if ((k = S->Sasiad_Poludniowo_Wschodni()) && k->podaj_stan() == stan)
		Sasiedzi++;

	return Sasiedzi;
}



inline int Zlicz_Niemartwych_Sasiadow(const Sasiedztwo_Moora *S)
{
	int Sasiedzi = 0;
	const Komorka *k;

	if ((k = S->Sasiad_Polnocny()) && k->podaj_stan())
		Sasiedzi++;
	if ((k = S->Sasiad_Poludniowy()) && k->podaj_stan())
		Sasiedzi++;
	if ((k = S->Sasiad_Zachodni()) && k->podaj_stan())
		Sasiedzi++;
	if ((k = S->Sasiad_Wschodni()) && k->podaj_stan())
		Sasiedzi++;
	if ((k = S->Sasiad_Polnocno_Zachodni()) && k->podaj_stan())
		Sasiedzi++;
	if ((k = S->Sasiad_Polnocno_Wschodni()) && k->podaj_stan())
		Sasiedzi++;
	if ((k = S->Sasiad_Poludniowo_Zachodni()) && k->podaj_stan())
		Sasiedzi++;
	if ((k = S->Sasiad_Poludniowo_Wschodni()) && k->podaj_stan())
		Sasiedzi++;

	return Sasiedzi;
}

#endif /* __HAVE_COMMON_H */
