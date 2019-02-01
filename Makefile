CC = clang -std=c11 -Weverything -Werror -Wno-language-extension-token

tour.js : tour.c tour.h Makefile
	/e/emsdk/emscripten/1.38.16/emcc -std=c11 -Weverything -Werror -Wno-unused-function -Wno-language-extension-token -O2 -s ASSERTIONS=1 -s EXPORTED_FUNCTIONS='["_getNextPointSerialize"]' -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall","cwrap"]' -o $@ $<

test : src/tour.h src/tour.c src/tour_tb.c Makefile
	$(CC) -DDEBUG -o tour.exe tour.c tour_tb.c
	./tour.exe

clean : Makefile
	rm -f tour.js tour.exe
