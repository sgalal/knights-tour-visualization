EMSDK_ENV_PATH = /f/Source/Repos/emsdk/emsdk_env.sh
TB_BUILD_TARGET = x86_64-pc-mingw64-gnu

default : tour.h tour_gen.cpp index.htm async.js action.js
	source $(EMSDK_ENV_PATH) && emcc tour_gen.cpp -Wall -O2 -std=gnu++14 --bind -o docs/tour.js
	cp index.htm docs/index.htm
	cp async.js docs/async.js
	uglifyjs action.js -o docs/action.js

cp-only : index.htm async.js action.js
	cp index.htm docs/index.htm
	cp async.js docs/async.js
	uglifyjs action.js -o docs/action.js

test : tour.h tour_tb.cpp
	clang++ tour_tb.cpp -Wall -std=gnu++14 -o tour.exe --target=$(TB_BUILD_TARGET)
	./tour

clean :
	rm -f docs/tour.wasm docs/tour.js docs/index.htm docs/async.js docs/action.js tour.exe
