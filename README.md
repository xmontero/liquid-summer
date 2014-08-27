# LIQUID SUMMER

- Liquid-summer is an SDL test program written by Xavi Montero.
- It currently paints a 3D starfield. I would like to add a 3D fractal.
- The goal is to have a test in C++ using SDL that can be cross compiled from Linux to Windows and Android.

-----------------------------------------------------------------------------
## Features

- Pixel-painted 3D rotating and expanding starfield.
- Click the mouse and drag to change the x and y angular speeds.

-----------------------------------------------------------------------------
## Compile

To cross compile this program for Windows from an Ubuntu, you do the following in the Linux bash:

    $ cd build
    $ rm -Rf *
    $ cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ../
    $ make
    $ cp -a /files/fluor/fluor_compiler_test/SDL2-2.0.3/x86_64-w64-mingw32/bin/*.dll .

Android is not tested yet. Help is welcome.

-----------------------------------------------------------------------------
## History

### 2014-08aug-27

- First usable version.
- Creates a starfield that simulates a galaxy.
- Tested in Ubuntu 14.04.1 LTS compiling for Win64 with mingw.

#### TODO:
- Adjust timings depending on elapsed time. Currently adjusted for ~25FPS which is mine.
- Track mouse down click position.
