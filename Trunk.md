Right now in the trunk directory, we have two files:
  * cameratest.cpp
  * compile.sh

cameratest.cpp is the C++ file that just shows some basic operations dealing with grabbing an image, splitting up the color planes and grabbing all the red pixels.  When I first added it, it was a C program, but I modified it to use the C++ API instead.  I think you guys will probably have an easier time with the C++ API instead of dealing with all the pointer hassle you'd find in the C API.

compile.sh is just a simple bash script right now that will compile it for you with gcc.
> Example: ./compile.sh cameratest
This will compile cameratest.cpp into the executable cameratest. This is linux only.