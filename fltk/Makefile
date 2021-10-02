
CXXFLAGS+=-g
CFLAGS+=-g

objs = gui.o widok.o

all: $(objs)

gui.o: gui.cxx
	g++ -g -c $^ -o $@



#all: $(patsubst  %.cpp,%.o,$(wildcard *.cc *.cxx *.cpp *.C)) \
#	  $(patsubst  %.c,%.o,$(wildcard *.c))
#	g++ -g $^

tags:
	ctags -R .

