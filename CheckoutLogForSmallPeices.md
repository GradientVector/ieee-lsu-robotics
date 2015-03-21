This is the list of functions we can begin writing. Next to each is a list of the functions that the function will call upon.
To work on a function, write **"`*`- Checked out by _YOUR\_NAME_`*`"** above it (include the asterisks to have the wiki page make it **bold**). Then write pseudocode or full C++, remembering to put a
title block comment. To check the code back in, erase your comment and put your code in the code repository on Google Code.
Title your source files functionNameHere.cpp and your pseudocode files functionNameHere.txt. For now all classes need their own folder in trunk/src/'classname' on Google Code; PS if you have an idea of a function to add to this list, or a modification to one of these functions, write it in a wiki-comment, and I'll modify the wiki page itself.



  * MCI **- Checked out by RAVI**
    * _void setVel(double)_		//sets velocity. highly dependent on our motor controllers **- checked out by Andrew**
    * _void setRotVel(double)_ 		//sets rotational velocity. highly dependent on our motor controllers **- checked out by Andrew**




  * VARIOUS INPUTS
    * _getVoltage()_               //OR: bool isFull(). monitors the charge on the capacitor
    * _bool isCharging()_          //to see if contact has been made and charge is flowing. this may just be a few calls to getVoltage() and a comparison to see if it's increasing
    * _bool isCharged()_           //to see if charge is at/near max capacity
    * _double voltageDerivative()_ //to see how fast the voltage is increasing. used to verify that we've made a connection.


  * VISION
    * _PixelPoint findObject(Cylinder)_  	     //finds one of the colored cylinder shapes in the image, and returns the x,y (pixels) location of the base of the object **- Checked out by John West**
    * _class PixelPoint_                          //an x and y coordinate. Can be used to represent a pixel-based location or a geographical/cartesian location.
    * _class CartesianPoint_              //will hold our location on the map
    * _class PolarPosition_               //another ordered pair, but by convention this will hold r and theta (see below) relative to our own position and direction
    * _PolarPosition placeObject(PixelPoint)_  //interprets the findObject() output (which is a Point), translating the Point (i.e. x,y coordinates) into an ordered pair representing: r, the distance from the camera to object, and theta, the angle of of rotation we WOULD have to do to point at the object. (positive angle mean turning left) **finished**
    * _class Cylinder_                       //contains



  * NAVIGATION
    * _class Bot_                         //holds our x,y position as a "Point", and the angle(degrees) in which the robot is pointing in a double. instantiated only once **DONE**
    * _void driveToMainLine()
    *_void followLineTo(Cylinder cyl)
    * _void homeInOn(Cylinder, double distance)_          //homes in on an object until it gets to a certain distance away from the object. uses setVeloctiy(), setRotationalVel(), findObject(), placeObject() **- Checked out by Harry**
    * _void pointTo(CartesianPoint)_              //uses our own x,y coordinates, our own angle, the the point's x,y coords to see how much we need to turn
    * _void chargeFor(...)
    *_void dischargeFor(...)




  * MAIN
> > _main()_                    //uses... everything. **- Checked out by Andrew Elias**