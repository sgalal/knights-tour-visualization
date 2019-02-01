tour.js : tour.c tour.h Makefile
	emcc -std=c11 -Weverything -Werror -Wno-unused-function -Wno-language-extension-token -O2 -s ASSERTIONS=1 -s EXPORTED_FUNCTIONS='["_getNextPointSerialize"]' -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall","cwrap"]' -o $@ $<

test : tour.exe

tour.exe : tour.h tour.c tour_tb.c Makefile
	clang -std=c11 -Weverything -Werror -Wno-language-extension-token -DDEBUG -o $@ tour.c tour_tb.c
	./tour.exe

clean : Makefile
	$(RM) tour.js tour.wasm tour.exe
