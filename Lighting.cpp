#include "Lighting.h"
#include "Plane.h"
#include "Sphere.h"
#include "Scene.h"

//calculates direction to light from a point x
glm::vec3 calculateDirection(const glm::vec3& p, const glm::vec3& x){
    glm::vec3 n, d, r;
    //numerator
    n= p-x;
    //denominator
    d= p-x;

    //result
    r=d/glm::length(d);
    return r;
}

glm::vec3 lambertianShading(glm::vec3 kd, glm::vec3 id, Object o){
    //you'll is collide for this and you need to ask jory about l hat 
    i_d*Object o.getMaterial().kd*max(0,);

}
