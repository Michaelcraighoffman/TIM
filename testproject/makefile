CC=g++
CPPFLAGS=-O0 -fPIC -I ../lib/include -fpermissive
OBJECTS=main.o testgraph.o testgray.o testsystem.o
OUTPUTDIR=../bin/
LIBS= -lti89pc

testproject : $(OBJECTS)
	$(CC) $(CPPFLAGS) -o$(OUTPUTDIR)testproject $(OBJECTS) $(LIBS)
clean:
	rm -f *.o
