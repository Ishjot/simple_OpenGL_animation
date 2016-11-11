all: main.cpp anim_cubes

SOURCES	= main.cpp
OBJS	= $(SOURCES:.cpp=.o)

.cpp.o:
	g++ -std=c++11 -c -Wall $< -o $@

anim_cubes: main.o
	g++ $(OBJS) -lGL -lGLU -lglut -lm $(LDFLAGS) -o $@

clean:
	rm -f *.o anim_cubes
