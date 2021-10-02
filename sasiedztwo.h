/*
 * Copyright (C) 2004,2005   Robert Nowotniak <robercik@stud.ics.p.lodz.pl>
 * Copyright (C) 2004,2005   Micha³ Ostrowski <mostrow@stud.ics.p.lodz.pl>
 *
 */
#ifndef __HAVE_SASIEDZTWO_H
#define __HAVE_SASIEDZTWO_H 1

#include "life.h"
#include "komorka.h"
#include "tablica_pol.h"

class Sasiedztwo_Neumanna  {
	protected:
		const Komorka *N;
		const Komorka *S;
		const Komorka *E;
		const Komorka *W;

	public:
		Sasiedztwo_Neumanna();
		Sasiedztwo_Neumanna(Tablica_Pol *T, int x, int y);
		Sasiedztwo_Neumanna(Komorka N, Komorka S, Komorka E, Komorka W);

		const Komorka* Sasiad_Polnocny() const;
		const Komorka* Sasiad_Poludniowy() const;
		const Komorka* Sasiad_Wschodni() const;
		const Komorka* Sasiad_Zachodni() const;
};


class Sasiedztwo_Moora : public Sasiedztwo_Neumanna {
	protected:
		const Komorka *NE;
		const Komorka *NW;
		const Komorka *SE;
		const Komorka *SW;

	public:
		Sasiedztwo_Moora();
		Sasiedztwo_Moora(Tablica_Pol *T, int x, int y);
		Sasiedztwo_Moora(Komorka NE, Komorka NW, Komorka SE, Komorka SW);

		const Komorka* Sasiad_Polnocno_Wschodni() const;
		const Komorka* Sasiad_Polnocno_Zachodni() const;
		const Komorka* Sasiad_Poludniowo_Wschodni() const;
		const Komorka* Sasiad_Poludniowo_Zachodni() const;
};



inline const Komorka*
Sasiedztwo_Neumanna::
Sasiad_Polnocny() const
{
	return N;
}

inline const Komorka*
Sasiedztwo_Neumanna::
Sasiad_Poludniowy() const
{
	return S;
}

inline const Komorka*
Sasiedztwo_Neumanna::
Sasiad_Wschodni() const
{
	return E;
}

inline const Komorka*
Sasiedztwo_Neumanna::
Sasiad_Zachodni() const
{
	return W;
}



inline const Komorka*
Sasiedztwo_Moora::
Sasiad_Polnocno_Wschodni() const
{
	return  NE;
}

inline const Komorka*
Sasiedztwo_Moora::
Sasiad_Polnocno_Zachodni() const
{
	return  NW;
}

inline const Komorka*
Sasiedztwo_Moora::
Sasiad_Poludniowo_Wschodni() const
{
	return  SE;
}

inline const Komorka*
Sasiedztwo_Moora::
Sasiad_Poludniowo_Zachodni() const
{
	return  SW;
}



#endif /* __HAVE_SASIEDZTWO_H */
