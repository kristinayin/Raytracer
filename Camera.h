#ifndef _CAMERA_H_
#define _CAMERA_H_

// GL
#include "GLInclude.h"
//#include "Ray.h" //not sure if we need this

struct Camera {
    Camera(const glm::vec3& _eye) : _eye(0, 0, 0);
    float focal = 1.0;//focal length from eye to view frame

    //next 3 lines represent where the camera is looking
    glm::vec3 u(1.f, 0.f, 0.f);
    glm::vec3 v(0.f, 1.f, 0.f);
    glm::vec3 w(0.f, 0.f, -1.f);
};

#endif