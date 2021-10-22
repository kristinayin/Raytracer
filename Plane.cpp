//
//  Plane.cpp
//  
//
//  Created by Kristina Yin on 10/22/21.
//

#include <vector>

using namespace std;
using namespace glm;

class Plane {
public:
    Plane() {
        point = vec3(0,0,0);
        normal = vec3(0,0,0);
    }
    
    /*
    Better way to set up constructors?
    Plane() : point(vec3(0,0,0)), normal(vec3(0,0,0)) {}
    ...something like that
    */
    
    Plane(int y, vec3 place) {
        point = place;
        normal = vec3(0,y,0);
    }
private:
    vec3 point;
    vec3 normal;
}
