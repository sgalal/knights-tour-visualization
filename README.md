# Knight's Tour Visualization

[![Build Status](https://travis-ci.org/chromezh/knights-tour-visualization.svg?branch=master)](https://travis-ci.org/chromezh/knights-tour-visualization) [![Build status](https://ci.appveyor.com/api/projects/status/a3t55hc7dcxlwlg2?svg=true)](https://ci.appveyor.com/project/chromezh/knights-tour-visualization) [![MIT Licence](https://badges.frapsoft.com/os/mit/mit.svg?v=103)](https://opensource.org/licenses/mit-license.php)

_Knight's tour visualization in C and JavaScript using divide and conquer algorithm. The route is shown in animation. _

Visit https://chromezh.github.io/knights-tour-visualization/ for details.

![Knight's Tour on a 14*14 board](demo.jpg)

## Build

**Prerequisites**

* [Emscripten](http://kripken.github.io/emscripten-site/)
* [UglifyJS](http://lisperator.net/uglifyjs/)

**Build Script**

Run `make` or `mingw32-make`. Then open `index.htm` in `docs` folder.

## Implementation

The code is an implementation of _Parberry, Ian. "An efficient algorithm for the Knight's tour problem." Discrete Applied Mathematics 73.3(1997):251-260_.
