#ifndef _CAMERA_H_
#define _CAMERA_H_

// GL
#include "GLInclude.h"
//#include "Ray.h" //not sure if we need this

struct Camera {
    Camera(const glm::vec3& _eye) : _eye(0, 0, 0);
    float focal = 1.0;//focal length from eye to view frame
};

#endif