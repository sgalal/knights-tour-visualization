EMSDK_ENV_PATH = /f/Source/Repos/emsdk/emsdk_env.sh

default : tour.cpp
	source $(EMSDK_ENV_PATH) && emcc tour.cpp -Wall -O2 -std=gnu++14 --bind -o tour.js

clean :
	rm -f tour.wasm tour.js
