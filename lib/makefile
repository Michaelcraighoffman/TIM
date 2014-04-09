CC=g++
CPPFLAGS=-O0 -fPIC -I ./include
OBJECTS=alloc.o __custom.o dialogs.o __fontimages.o graph.o gray.o intr.o kbd.o link.o mem.o __once.o sprites.o stdlib.o stub.o system.o __timallegro.o __timsystem.o
LIBS=`allegro-config --libs`

libti89pc.so : $(OBJECTS)
	$(CC) $(CPPFLAGS) -shared -Wl,-soname,ti89pc -olibti89pc.so $(OBJECTS) $(LIBS)
install:
	cp libti89pc.so /usr/lib
	ldconfig
clean:
	rm -f *.o libti89pc.so
