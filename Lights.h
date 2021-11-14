#ifndef _LIGHTS_H_
#define _LIGHTS_H_

#include "GLInclude.h"
#include "Lighting.h"
#include <vector>

class Lights{
     std::vector<Light> l;
     void addLight(const Light& lgt){
         l.pushBack(lgt);
     }
}

#endif