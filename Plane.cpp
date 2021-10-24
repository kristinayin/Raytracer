//
//  Plane.cpp
//  
//
//  Created by Kristina Yin on 10/22/21.
//
#include "Plane.h"

Collision Plane:: collide(const Ray& _ray) const {

    glm::vec3 x;//point of collision on plane

    float detectCollision = glm::dot(_ray.m_direction, normal);//check if direction dot normal isn't 0
    if(detectCollision > 0){
        float t = (glm::dot((point - _ray.m_origin), normal))/(detectCollision);

        if(t>0){
            x = _ray.at(t);
            Collision hit(x, normal, m_material);//might need to change this function a bit; not sure if we need material
            return hit;
        }
    }

    return Collision();
}

//using namespace std;
//using namespace glm;


/*
class Plane {
public:
//private: //making this private because its causing an out of scope error
    glm::vec3 point;
    glm::vec3 normal;
    Plane() {
        point = glm::vec3(0,0,0);
        normal = glm::vec3(0,0,0);
    }
    
    
    Better way to set up constructors?
    Plane() : point(vec3(0,0,0)), normal(vec3(0,0,0)) {}
    ...something like that
    
    
    Plane(int y, glm::vec3 place) {
        point = place;
        normal = glm::vec3(0,y,0);
    }

};
*/