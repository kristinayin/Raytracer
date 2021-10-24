//
//  Plane.cpp
//  
//
//  Created by Kristina Yin on 10/22/21.
//
#include "GLInclude.h"
#include <vector>

//using namespace std;
//using namespace glm;

class Plane {
public:
//private: //making this private because its causing an out of scope error
    glm::vec3 point;
    glm::vec3 normal;
    Plane() {
        point = glm::vec3(0,0,0);
        normal = glm::vec3(0,0,0);
    }
    
    /*
    Better way to set up constructors?
    Plane() : point(vec3(0,0,0)), normal(vec3(0,0,0)) {}
    ...something like that
    */
    
    Plane(int y, glm::vec3 place) {
        point = place;
        normal = glm::vec3(0,y,0);
    }

};
