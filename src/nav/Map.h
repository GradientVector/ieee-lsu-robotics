#ifndef MAP_H
#define MAP_H

#include "../util/Cylinder.h"
#include "../util/util.h"

//a list of cylinders (and their colors/locations)
class Map {
	public:
	Cylinder yellowCyl;
	Cylinder blueCyl;
	Cylinder greenCyl;
	Cylinder redCyl;
	
    //TODO: lines? should they be on the map? maybe

	Map();
};

#endif
