#include <emscripten/bind.h>

using namespace emscripten;

#include "tour.h"

EMSCRIPTEN_BINDINGS(my_module)
{
    class_ <Point> ("Point");
    function("getFirst", getFirst);
    function("getSecond", getSecond);
    function("nextPoint", nextPoint);
}
