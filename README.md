# LIQUID SUMMER

- Liquid-summer is an SDL test program written by Xavi Montero.
- It currently paints a 3D starfield in the form of a galaxy or a fractal.
- The goal is to have a test in C++ using SDL that can be cross compiled from Linux to Windows and Android.

-----------------------------------------------------------------------------
## Features

- Pixel-painted 3D rotating and expanding starfield (galaxy or fractal).
- Click the mouse and drag to change the x and y angular speeds.

-----------------------------------------------------------------------------
## Compile

To cross compile this program for Windows from an Ubuntu, you do the following in the Linux bash:

    $ cd build
    $ rm -Rf *
    $ cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ../
    $ cp -a /files/fluor/fluor_compiler_test/SDL2-2.0.3/x86_64-w64-mingw32/bin/*.dll .
    $ make

then if you change the code

    $ make

if make gets weird (maybe editing a .h or the CMakeLists.txt):

    $ make rebuild_cache
    $ make clean
    $ make

Android is not tested yet. Help is welcome.

-----------------------------------------------------------------------------
## History

### 2014-08aug-28

- Added a 2D fractal, rotating in a 3D space.
- Press 1 and 2 to switch between a galaxy and a fractal.

### 2014-08aug-27

- First usable version.
- Creates a starfield that simulates a galaxy.
- Tested in Ubuntu 14.04.1 LTS compiling for Win64 with mingw.

#### TODO:
- Adjust timings depending on elapsed time. Currently adjusted for ~25FPS which is mine.
- Track mouse down click position.
