EMSDK_ENV_PATH = /f/Source/Repos/emsdk/emsdk_env.sh

default : tour.h tour_gen.cpp index.htm
	source $(EMSDK_ENV_PATH) && emcc tour_gen.cpp -Wall -O2 -std=gnu++14 --bind -o docs/tour.js
	cp index.htm docs/index.htm

test : tour.h tour_tb.cpp
	clang++ tour_tb.cpp -Wall -std=gnu++14 -o tour.exe
	./tour

clean :
	rm -f docs/tour.wasm docs/tour.js tour.exe
