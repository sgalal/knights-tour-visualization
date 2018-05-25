EMSDK_ENV_PATH = /f/Source/Repos/emsdk/emsdk_env.sh
TB_BUILD_TARGET = x86_64-pc-mingw64-gnu

default : tour.h tour_gen.cpp index.htm draw.js
	source $(EMSDK_ENV_PATH) && emcc tour_gen.cpp -Wall -O2 -std=gnu++14 --bind -o docs/tour.js
	cp index.htm docs/index.htm
	cp draw.js docs/draw.js

test : tour.h tour_tb.cpp
	clang++ tour_tb.cpp -Wall -std=gnu++14 -o tour.exe --target=$(TB_BUILD_TARGET)
	./tour

clean :
	rm -f docs/tour.wasm docs/tour.js tour.exe
