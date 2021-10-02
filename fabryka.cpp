/*
 * Copyright (C) 2004,2005   Robert Nowotniak <robercik@stud.ics.p.lodz.pl>
 * Copyright (C) 2004,2005   Micha³ Ostrowski <mostrow@stud.ics.p.lodz.pl>
 *
 */

#include <cassert>
#include <FL/fl_ask.H>
#include "life.h"
#include "fabryka.h"
#include "srodowisko.h"


Fabryka_Komorek::Zbior_Komorek Fabryka_Komorek::pula;
Fabryka_Warunkow_Srodowiska::Zbior_Warunkow_Srodowiska Fabryka_Warunkow_Srodowiska::pula;
Fabryka_Funkcji::Tabela_Modulow Fabryka_Funkcji::pula;

/*
 * Definicje metod Fabryki Komorek
 *
 */

class Pred_Zgodny_Typ {
	const int typ;
	public:
		Pred_Zgodny_Typ(int t)
			: typ(t)  { }
		bool operator()(const Komorka & K)
		{
			return K.podaj_typ() == typ;
		}
};
	

const Komorka* Fabryka_Komorek::
Nowa_Komorka(int typ, int stan)
{
	Zbior_Komorek::iterator iter;
	iter = pula.find(Komorka(typ, Komorka::funkcja_przejscia(0), stan));

	if (iter != pula.end())
		return &*iter;

	iter = find_if(pula.begin(), pula.end(), Pred_Zgodny_Typ(typ));

	// 
	// Je¶li nie znaleziono, to wyst±pi³a pro¶ba o komórkê,
	// któr± nie wiadomo jak zrobiæ (?) -- nieznanego typu.
	//
	assert(iter != pula.end());

#ifdef HAVE_FLTK
	Komorka K(typ, iter->funkcja(), stan, iter->kolor());
#else
	Komorka K(typ, iter->funkcja(), stan);
#endif
	K.nazwa(iter->nazwa());
	K.modul(iter->modul());

	return &*pula.insert(K).first;
}

void 
Fabryka_Komorek::
Nowy_Rodzaj_Komorki(int typ, Komorka::funkcja_przejscia funkcja)
{
	Fabryka_Komorek::pula.insert(Komorka(typ, funkcja));
}



/*
 * Zmienienie nazw komórkom o danym typie
 */
void
Fabryka_Komorek::
Zmien_Parametry(int typ, std::string nazwa)
{
	Zbior_Komorek::iterator iter = pula.begin();
	while (iter != pula.end()) {
		iter = find_if(iter, pula.end(), Pred_Zgodny_Typ(typ));
		if (iter != pula.end()) {
			iter->nazwa(nazwa);
			iter++;
		}
	}
}

/*
 * Zmienienie funkcji przej¶cia i informacji o module komórkom o danym typie
 */
void
Fabryka_Komorek::
Zmien_Parametry(int typ, std::string modul, Komorka::funkcja_przejscia f)
{
	Zbior_Komorek::iterator iter = pula.begin();
	while (iter != pula.end()) {
		iter = find_if(iter, pula.end(), Pred_Zgodny_Typ(typ));
		if (iter != pula.end()) {
			iter->modul(modul);
			iter->funkcja(f);
			iter++;
		}
	}
	
}

#ifdef HAVE_FLTK
/*
 * Zmienienie koloru komórkom o danym typie
 */
void
Fabryka_Komorek::
Zmien_Parametry(int typ, Fl_Color kolor)
{
	Zbior_Komorek::iterator iter = pula.begin();
	while (iter != pula.end()) {
		iter = find_if(iter, pula.end(), Pred_Zgodny_Typ(typ));
		if (iter != pula.end()) {
			iter->kolor(kolor);
			iter++;
		}
	}
}
#endif


Wektor_Int
Fabryka_Komorek::
Podaj_Typy()
{
	Wektor_Int ret;
	Zbior_Komorek::iterator iter;

	iter = pula.begin();
	while (iter != pula.end()) {
		ret.push_back(iter->podaj_typ());
		iter++;
	}

	/*
	 * Usuniêcie duplikatów
	 */
	sort(ret.begin(), ret.end());
	return Wektor_Int(ret.begin(), unique(ret.begin(), ret.end()));
}


const Komorka*
Fabryka_Komorek::
Podaj_Komorke(int typ)
{
	Zbior_Komorek::iterator iter;
	iter = find_if(pula.begin(), pula.end(), Pred_Zgodny_Typ(typ));
	return iter == pula.end() ? 0 : &*iter;
}

void
Fabryka_Komorek::
Wyczysc_Pule()
{
	pula.clear();
}



/*
 * Definicje metod Fabryki Warunków ¦rodowiska
 *
 */


const Warunki_Srodowiska*
Fabryka_Warunkow_Srodowiska::
Nowe_Warunki(std::string N, double w, double o, double t
#ifdef HAVE_FLTK
				, Fl_Color k
#endif
		)
{
	Zbior_Warunkow_Srodowiska::iterator iter;
	iter = pula.find(Warunki_Srodowiska(N));

	if (iter != pula.end())
		return &*iter;

#ifdef HAVE_FLTK
	Warunki_Srodowiska W(N, w, o, t, k);
#else
	Warunki_Srodowiska W(N, w, o, t);
#endif
	return &*pula.insert(W).first;
}


void Fabryka_Warunkow_Srodowiska::
Zmien_Parametry(std::string N, double w, double o, double t
#ifdef HAVE_FLTK
		, Fl_Color k
#endif
		)
{
	Zbior_Warunkow_Srodowiska::iterator iter;
	iter = pula.find(Warunki_Srodowiska(N));

	/*
	 * Proba zmiany warunkow, ktorych nie ma w puli?
	 */
	assert(iter != pula.end());


	/*
	 * Nale¿y zmieniæ parametry Warunkow Srodowiska o nazwie N,
	 * ale nie jest zmieniana nazwa, na której opiera siê relacja
	 * porz±dkuj±ca Warunków, u¿ywana przez pulê (std::set).
	 * Zostanie wiêc zachowana ,,sta³o¶æ logiczna'' obiektu.
	 */
	const Warunki_Srodowiska *p =(&*iter);

	p->_wilgotnosc = w;
	p->_oswietlenie = o;
	p->_temperatura = t;
#ifdef HAVE_FLTK
	p->_kolor = k;
#endif

}


void
Fabryka_Warunkow_Srodowiska::
Usun_Warunki(std::string N)
{
	pula.erase(Warunki_Srodowiska(N));
}

Wektor_String
Fabryka_Warunkow_Srodowiska::
Podaj_Nazwy()
{
	Wektor_String ret;
	Zbior_Warunkow_Srodowiska::iterator iter;

	iter = pula.begin();
	
	while (iter != pula.end()) {
		ret.push_back(iter->nazwa);
		iter++;
	}

	return ret;
}


void
Fabryka_Warunkow_Srodowiska::
Wyczysc_Pule()
{
	pula.clear();
}


/*
 * Definicje metod Fabryki Funkcji
 *
 */

Komorka::funkcja_przejscia
Fabryka_Funkcji::
Zaladuj_Funkcje(std::string modul)
{
	Tabela_Modulow::iterator iter;
	Komorka::funkcja_przejscia f;

	/*
	 * Je¶li ten modu³ by³ ju¿ za³adowany, nie robiæ tego ponownie.
	 */
	if ((iter = pula.find(modul)) != pula.end())
		return iter->second.second;
	else  {
		/*
		 * Za³adowanie funkcji z modu³y (zale¿ne od systemu)
		 */

#ifdef LINUX
		void *uchwyt;

		uchwyt = dlopen(modul.c_str(), RTLD_NOW);
		if (!uchwyt) {
#ifdef HAVE_FLTK
			fl_alert("Nie uda³o siê otworzyæ pliku modu³u.");
#endif
			return 0;
		}

		*(void**)(&f) = dlsym(uchwyt, "funkcja");

		if (dlerror() != 0) {
#ifdef HAVE_FLTK
			fl_alert("Nie uda³o siê za³adowaæ funkcji przejscia z modu³u.");
#endif
			dlclose(uchwyt);
			return 0;
		}

		pula[modul] = std::pair<void*, Komorka::funkcja_przejscia>(uchwyt, f);

#else /* nie LINUX */
#ifdef WIN32
		HINSTANCE uchwyt; 

		uchwyt = LoadLibrary(TEXT(modul.c_str()));
		if (!uchwyt) {
#ifdef HAVE_FLTK
			fl_alert("Nie uda³o siê otworzyæ pliku modu³u.");
#endif
			return 0;
		}

		f = (Komorka::funkcja_przejscia)GetProcAddress(uchwyt, TEXT("funkcja")); 

		if (! f) {
#ifdef HAVE_FLTK
			fl_alert("Nie uda³o siê za³adowaæ funkcji przejscia z modu³u.");
#endif
			FreeLibrary(uchwyt); 
			return 0;
		}

		pula[modul] = std::pair<HINSTANCE, Komorka::funkcja_przejscia>(uchwyt, f);
#endif /* nie Win32 */
#endif
	}
	return f;
}

void
Fabryka_Funkcji::
Wyczysc_Pule()
{
	Tabela_Modulow::iterator iter = pula.begin();

	while (iter != pula.end()) {
#ifdef LINUX
		dlclose(iter->second.first);
#else
#ifdef WIN32
		FreeLibrary(iter->second.first); 
#endif
#endif
		pula.erase(iter);
		iter++;
	}
}

