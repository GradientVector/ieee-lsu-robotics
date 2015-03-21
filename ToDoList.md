TODO list:

---


Make sure our .cpp files compile. They should be checked in order from simplest/smallest to largest/complexest. The following still need to be checked:
  * Camera.cpp
  * PhysicalLine.cpp (may not even be used...)
  * mci.cpp
  * vision.cpp



We need to check our makefiles to make sure they are all doing the right things.

Blob recognition of a given color. Shape is not important, we just need the centroid of the 'blob' of color.

Test the motor controller with a motor controller test file. Just see if the basic mci functions work.

Put functionality into our movement functions that keeps track of our position and angle.

Bot.h/cpp's function called goToLineAndFollowItTo(Cylinder cyl, double distance) needs to be worked on.

On approximately line 13 of vision.cpp, there is a char which has multiple characters/digits assigned to it. Compiler is complaining

John West: grayImage, color, and checkArea all need to be put into versioning if they aren't already, and they need to be made accessible to Camera.h

run throught all code which uses PolarPoint and make sure it uses the getTh() and getR() methods instead of accessing the variables directly