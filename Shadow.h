#ifndef _SHADOW_H_
#define _SHADOW_H_

#include <GLInclude.h>

#include

class Shadow{

}

#endif

//if camera intersects point on sphere
    //  do additional ray tracing  from point of collision to the light source
    //  if point on sphere intersects at light source only, apply ADS
    //  else apply only ambient lighting (when point on sphere intersects another point on sphere)