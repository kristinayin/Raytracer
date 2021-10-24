#ifndef _CAMERA_H_
#define _CAMERA_H_

// GL
#include "GLInclude.h"
//#include "Ray.h" //not sure if we need this

struct Camera{
    //Camera() : _eye(0, 0, 0), u(1, 0, 0), v(0, 1, 0), w(0, 0, -1), focal(1) {}

    glm::vec3 _eye(0, 0, 0), u(1, 0, 0), v(0, 1, 0), w(0, 0, -1);
    float focal = 1;
};

#endif