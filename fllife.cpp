/*
 * Copyright (C) 2004,2005   Robert Nowotniak <robercik@stud.ics.p.lodz.pl>
 * Copyright (C) 2004,2005   Micha³ Ostrowski <mostrow@stud.ics.p.lodz.pl>
 *
 */
#include <cstdio>
#include <cstdlib>
#include <clocale>
#include "life.h"
#include "gui.h"
#include "widok.h"
#include "komorka.h"


/*
 * Przejmuje wszystkie skróty klawiaturowe
 * [Nie chcemy domy¶lnych]
 */
static int
handle(int i)
{
	  return i == FL_SHORTCUT;
}


int
main()
{
	Fl::add_handler(handle);

	setlocale(LC_ALL, "");
	PL_Font = FL_FREE_FONT;

#ifdef LINUX
	const char *font = "-*-verdana-*-r-*-*-11-*-*-*-*-*-iso8859-2";
#else
#ifdef WIN32
	const char *font = "Verdana";
#endif
#endif

	Fl::set_fonts(font);
	Fl::set_font(PL_Font, font);
	fl_message_font(PL_Font, 14);


	fclose(stdin);
	fclose(stdout);
	fclose(stderr);


	UserInterface();

	return Fl::run();
}

