all:
	make -C lib

library:
	make -C lib

checkers:
	make -C ticheckers

tests:
	make -C testproject
	make -C ticheckers

install:
	make -C lib install

clean:
	make -C lib clean
	make -C testproject clean
	make -C ticheckers clean
	rm -f ./bin/checkers


