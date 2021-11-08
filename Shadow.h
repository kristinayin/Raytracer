#ifndef _SHADOW_H_
#define _SHADOW_H_

#include <GLInclude.h>

#include <Plane.h>
#include <Lighting.h>

class Shadow{

}

#endif

//make a glm::vec3 that goes from plane to light
//glm::vec3 l - glm::vec3 p = direction d; l is light and p is point of collision
//ray eqn: x = p + td, where x = l
//apply ray collision, prob using concept of a plane collision?


//if camera intersects point on plane
    //  do additional ray tracing from point of collision on plane to the light source
    //  if ray from plane intersects a point on sphere
    //      apply ambient lighting on that spot