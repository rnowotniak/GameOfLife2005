CXXFLAGS=-I../.. -I../../fltk -I../../Funkcje_Przejscia -march=i686 -mcpu=i686 -O3 -ffast-math -fexpensive-optimizations

all: jadro.so mielina.so neuron.so otoczenie.so

%.so: %.o
	g++ $(CXXFLAGS) -shared -fPIC $^ -o $@
	strip $@

clean:
	-rm *.so *.o

