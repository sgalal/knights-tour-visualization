EMSDK_ENV_PATH = /f/Source/Repos/emsdk/emsdk_env.sh

default : tour.h tour_gen.cpp
	source $(EMSDK_ENV_PATH) && emcc tour_gen.cpp -Wall -O2 -std=gnu++14 --bind -o tour.js

test : tour.h tour_tb.cpp
	clang++ tour_tb.cpp -Wall -std=gnu++14 -o tour.exe
	./tour

clean :
	rm -f tour.wasm tour.js
