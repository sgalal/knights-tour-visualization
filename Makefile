EMSDK_ENV_PATH = /f/Source/Repos/emsdk/emsdk_env.sh
TB_BUILD_TARGET = x86_64-pc-mingw64-gnu

default : src/tour.h src/tour_gen.cpp src/index.htm src/async.js src/action.js
	source $(EMSDK_ENV_PATH) && emcc src/tour_gen.cpp -Wall -Wno-missing-braces -O2 -std=gnu++14 --bind -o docs/tour.js
	cp src/index.htm docs/index.htm
	cp src/async.js docs/async.js
	uglifyjs src/action.js -o docs/action.js

cp-only : src/index.htm src/async.js src/action.js
	cp src/index.htm docs/index.htm
	cp src/async.js docs/async.js
	uglifyjs src/action.js -o docs/action.js

test : src/tour.h src/tour_tb.cpp
	clang++ src/tour_tb.cpp -Weverything -std=gnu++14 -o docs/tour.exe -Wno-c++98-compat -Wno-global-constructors -Wno-exit-time-destructors --target=$(TB_BUILD_TARGET)
	./docs/tour

clean :
	rm -f docs/tour.wasm docs/tour.js docs/index.htm docs/async.js docs/action.js docs/tour.exe
