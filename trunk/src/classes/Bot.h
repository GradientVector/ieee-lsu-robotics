/**
Filename:	Bot.h

Bot class. represents our robot. holds the location and angle info.
Will only be instantiated once.

author:		Andrew Elias
		
Log:		
	Mar 1 2011 - created by Andrew Elias
*/

//will only be instantiated once. represents the robot itself.
//Holds location and angle information.
class Bot {
	public:
		CartesianPoint location;
		Angle angle;
};
