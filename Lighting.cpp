#include "Lighting.h"
#include "Plane.h"
#include "Sphere.h"
#include "Scene.h"
#include "Object.h"
#include "Ray.h"

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

glm::vec3 Light:: lambertianShading(Ray x, Plane o){
    //you'll use isCollide for this and you need to ask jory about l hat 
    glm::vec3 l = calculateDirection(x.m_origin, point);

    return o.getMaterial().kd*i_d*max(0, dot(o.getNormal(),l));//how do you find the normal 
}

glm::vec3 Light:: blinPhongShading(Ray x, Plane o, Camera c){
    glm::vec3 v = calculateDirection(x.m_origin,c.eye_)
    glm::vec3 l = calculateDirection(x.m_origin, point);
    glm::vec3 h = glm::normalize(v+l);
    return o.getMaterial().ks*i_s*max(0,dot(v,h));

}
