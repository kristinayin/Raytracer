//
//  Plane.cpp
//  
//
//  Created by Kristina Yin on 10/22/21.
//
#include "Plane.h"

//Frankie Z.
Collision Plane:: collide(const Ray& _ray) const {

    glm::vec3 x;//point of collision on plane

    float detectCollision = glm::dot(_ray.m_direction, normal);//check if direction dot normal isn't 0
    if(detectCollision != 0){
        float t = (glm::dot((point - _ray.m_origin), normal))/(detectCollision);

        if(t>0.001){
            x = _ray.at(t);
            Collision hit(x, normal, &m_material, t);//calculate collision point on plane
            //apply lighting computation here (most likely shadowing effects)
            return hit;
        }
    }

    return Collision();
}

