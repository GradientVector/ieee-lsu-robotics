This is an eve-bot I wrote, not really applicable to what we're doing right now but it has both the C and C++ example API of OpenCV.  If you bother to read through it you might be able to find some useful stuff.

The initial code in the **bot** directory is the C API, and in the **bot/test** directory is the C++ API.  I never fully finished the C++ API section, but it does have a lot of work done on it, and it also has some of the same functions written in both APIs if you want to compare.

Also, there are other cool things in there, the XInput class, which allows mouse control and keyboard output in the XWindows environment for **nix, and the Qt based screencap function, which allows you to import a screencap directly into your program as an OpenCV image/matrix.**


You'll need to install OpenCV, Qt4, and probably some dev files for XWindows.