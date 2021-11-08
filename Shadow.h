#ifndef _SHADOW_H_
#define _SHADOW_H_

#include <GLInclude.h>

#include <Plane.h>
#include <Lighting.h>

class Shadow{

}

#endif

//make a glm::vec3 that goes from plane to light

//if camera intersects point on plane
    //  do additional ray tracing from point of collision on plane to the light source
    //  if ray from plane intersects a point on sphere
    //      apply ambient lighting on that spot