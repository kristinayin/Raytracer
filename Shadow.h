#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "GLInclude.h"

#include "Plane.h"
#include "Sphere.h"
#include "Lighting.h"
#include "Collision.h"
#include "Object.h"
#include "Material.h"
/*
class Shadow{

   Collision makeShadow(const vector& <Light> lights, const Object& obj, const Ray& _ray);//maybe collision func?

}
*/
#endif

//make a glm::vec3 that goes from plane/sphere to light
//glm::vec3 l - glm::vec3 p = direction d; l is light and p is point of collision
//ray eqn: x = p + td, where x = l
//apply ray collision, prob using concept of a plane collision?


//if camera intersects any object (plane/sphere)
    //  do additional ray tracing from point of collision to the light source
    //  if ray from plane intersects any other object
    //      apply ambient lighting on that spot