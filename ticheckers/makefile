CC=g++
CPPFLAGS=-O0 -fPIC -I ../lib/include
OBJECTS=ai.o checkers.o gameplay.o gfx.o state.o util.o
OUTPUTDIR=../bin/
LIBS= -lti89pc

checkers : $(OBJECTS)
	mkdir $(OUTPUTDIR)
	$(CC) $(CPPFLAGS) -o$(OUTPUTDIR)checkers $(OBJECTS) $(LIBS)
clean:
	rm -f *.o
