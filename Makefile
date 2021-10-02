
incs = -I. -Ifltk
CXXFLAGS+=$(incs) -mcpu=i686 -march=i686 -O3 -pipe -ffast-math -fexpensive-optimizations
CFLAGS+=$(incs)
LDFLAGS=-ldl # -lefence

funkcje_przejscia = \
	Funkcje_Przejscia/1d-150.o \
	Funkcje_Przejscia/3stany.o \
	Funkcje_Przejscia/amazing.o \
	Funkcje_Przejscia/amoeba.o \
	Funkcje_Przejscia/artist.o \
	Funkcje_Przejscia/brians_brain.o \
	Funkcje_Przejscia/conway.o \
	Funkcje_Przejscia/coral.o \
	Funkcje_Przejscia/highlife.o \
	Funkcje_Przejscia/replicator.o \
	Funkcje_Przejscia/seeds.o \
	Funkcje_Przejscia/sierpinski.o \
	Funkcje_Przejscia/walled_cities.o


objs = \
	ekosystem.o fabryka.o komorka.o sasiedztwo.o

all: fllife

tui: $(objs) main.o
	g++ $(CXXFLAGS) $(LDFLAGS) $^ -o life

objs: $(objs)


Funkcje_Przejscia: $(funkcje_przejscia)

moduly_linux: $(funkcje_przejscia)
	make -e -C Funkcje_Przejscia

%.o: %.cxx
	g++ $(CXXFLAGS) -c $^ -o $@


fllife.o: fllife.cpp
	g++ $(CXXFLAGS) -c $^ -o $@

fllife: $(objs) fllife.o fltk/widok.o fltk/gui.o
	g++ $(CXXFLAGS) $(LDFLAGS) `fltk-config --cxxflags --ldflags` -o $@ $^

tags:
	ctags -R .

clean:
	-rm *.o a.out core gmon.out life fllife tags fltk/*.o
#	-rm Funkcje_Przejscia/*.o Funkcje_Przejscia/*.so

