CXXFLAGS=-I.. -I../fltk -march=i686 -mcpu=i686 -O3 -ffast-math -fexpensive-optimizations

all: \
	1d-150.so \
	amazing.so \
	artist.so \
	brians_brain.so \
	3stany.so \
	amoeba.so \
	conway.so \
	coral.so \
	highlife.so \
	maze_race.so \
	replicator.so \
	seeds.so \
	ring.so \
	sierpinski.so \
	walled_cities.so \
	wire_world.so

%.so: %.o
	g++ $(CXXFLAGS) -shared -fPIC $^ -o $@
	strip $@

clean:
	-rm *.so *.o

