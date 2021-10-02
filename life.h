/*
 * Copyright (C) 2004,2005   Robert Nowotniak <robercik@stud.ics.p.lodz.pl>
 * Copyright (C) 2004,2005   Micha³ Ostrowski <mostrow@stud.ics.p.lodz.pl>
 *
 */
#ifndef __HAVE_LIFE_H
#define __HAVE_LIFE_H 1

/*
 * System operacyjny
 */
#define LINUX 1
// #define WIN32 1


#ifndef PATH_MAXLEN
#define PATH_MAXLEN 255
#endif


/*
 * Czy jest u¿ywana biblioteka FLTK do graficznego interfejsu u¿ytkownika
 */
#define HAVE_FLTK 1


/*
 * Katalog z gotowymi ekosystemami (*.eko)
 */
#define KATALOG_EKOSYSTEMOW "Ekosystemy"


/*
 * Katalog z gotowymi zbiorami uk³adów komórek (*.LIF)
 */
#define KATALOG_UKLADOW "Uklady"



/*
 * Katalog z funkcjami przejscia
 */
#define KATALOG_WTYCZEK "Funkcje_Przejscia"



#if !defined(LINUX) && !defined(WIN32)
#error "Nie zosta³a ustawione definicja preprocesora LINUX ani WIN32"
#endif
#if defined(LINUX) && defined(WIN32)
#error "S± ustawione jednocze¶nie definicje preprocesora LINUX i WIN32"
#endif


#endif /* __HAVE_LIFE_H */
