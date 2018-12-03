EMCC = emcc -std=gnu11 -Weverything -Werror -Wno-unused-function -Wno-language-extension-token -O2 -s ASSERTIONS=1
CC   = clang -std=gnu11 -Weverything -Werror -Wno-language-extension-token

default : docs/tour.js docs/index.htm docs/action.js

docs/tour.js : src/tour.h src/tour.c Makefile
	$(EMCC) -s EXPORTED_FUNCTIONS='["_getNextPointSerialize"]' -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' -o docs/tour.js src/tour.c

docs/index.htm : src/index.htm Makefile
	cp src/index.htm docs/index.htm

docs/action.js : src/action.js Makefile
	cp src/action.js docs/action.js

test : src/tour.h src/tour.c src/tour_tb.c Makefile
	$(CC) -DDEBUG -o docs/tour.exe src/tour.c src/tour_tb.c
	./docs/tour

clean : Makefile
	rm -f docs/*
