BUILD_PATH      = docs/
EMSDK_ENV_PATH  = /f/Source/Repos/emsdk/emsdk_env.sh
EMCC            = emcc -std=gnu11 -Weverything -Werror -Wno-unused-function -Wno-language-extension-token -O2 -s ASSERTIONS=1
CC              = clang -std=gnu11 -Weverything -Werror -Wno-language-extension-token

default : src/tour.h src/tour.c src/index.htm src/async.js src/action.js
	source $(EMSDK_ENV_PATH) && $(EMCC) -s EXPORTED_FUNCTIONS='["_getNextPointSerialize"]' -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' -o $(BUILD_PATH)tour.js src/tour.c
	cp src/index.htm $(BUILD_PATH)index.htm
	cp src/async.js $(BUILD_PATH)async.js
	uglifyjs src/action.js -o $(BUILD_PATH)action.js

cp-only : src/index.htm src/async.js src/action.js
	cp src/index.htm $(BUILD_PATH)index.htm
	cp src/async.js $(BUILD_PATH)async.js
	uglifyjs src/action.js -o $(BUILD_PATH)action.js

test : src/tour.h src/tour.c src/tour_tb.c
	$(CC) -DDEBUG -o $(BUILD_PATH)tour.exe src/tour.c src/tour_tb.c
	./$(BUILD_PATH)tour

clean :
	rm -f $(BUILD_PATH)tour.wasm $(BUILD_PATH)tour.js $(BUILD_PATH)index.htm $(BUILD_PATH)async.js $(BUILD_PATH)action.js $(BUILD_PATH)tour.exe
