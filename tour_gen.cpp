#include <emscripten/bind.h>

using namespace emscripten;

#include "tour.h"

EMSCRIPTEN_BINDINGS(my_module)
{
    class_ <Point> ("Point");
    function("make_point", make_point);
    function("getFirst", getFirst);
    function("getSecond", getSecond);
    function("nextPoint", nextPoint);
}
