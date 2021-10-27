#include "Lighting.h"
#include "Plane.h"
#include "Sphere.h"

glm::vec3 calculateDirection(const glm::vec3& p,const glm::vec3& x){
    glm::vec3 n, d, r;
    n= p-x;
    d= p-x;
    r=d/glm::length(d);
    return r;
}

//glm::vec3
