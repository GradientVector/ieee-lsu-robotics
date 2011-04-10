#ifndef LINE_H
#define LINE_H

#include "../util/PolarPoint.h"

/*
Line class. Represents the physical line or line segment, as it is interpreted by our vision. 
Naturally, the information is limited, because we cannot always see the entire thing.
*/

class PhysicalLine {
    private:
    PolarPoint closePoint, farPoint;            //the endpoints of the line segment that we can see
    bool closePointExtends, farPointExtends;    //whether or not each point extends beyond our field of vision
    
    

    public:
    Line(PolarPoint inputClosePoint, PolarPoint inputFarPoint);
    

}

#endif  //LINE_H
