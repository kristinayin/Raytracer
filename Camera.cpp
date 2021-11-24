#include "Camera.h"

//this function is for model matrix (model -> world transformation)
glm::mat4 Camera::transform(float tx, float ty, float tz, float radX, float radY, float radZ, float sx, float sy, float sz){
    glm::mat4 translation = glm::mat4(1.0, 0.0, 0.0, 0.0
                                        0.0, 1.0, 0.0, 0.0
                                        0.0, 0.0, 1.0, 0.0
                                        tx,  ty,  tz,  1.0);
            
    glm::mat4 scaling = glm::mat4(sx, 0.0, 0.0, 0.0
                                  0.0, sy, 0.0, 0.0
                                  0.0, 0.0, sz, 0.0
                                  0.0,  0.0, 0.0, 1.0);
            
    glm::mat4 xrot = glm::mat4(1.0, 0.0, 0.0, 0.0
                               0.0, cos(radX), -sin(radX), 0.0
                               0.0, sin(radX), cos(radX), 0.0
                               0.0,  0.0, 0.0, 1.0);

    glm::mat4 yrot = glm::mat4(cos(radY), 0.0, sin(radY), 0.0
                               0.0, 1.0,  0.0, 0.0
                               -sin(radY), 0.0, cos(radY), 0.0
                               0.0,  0.0, 0.0, 1.0);

    glm::mat4 zrot = glm::mat4(cos(radZ), -sin(radZ), 0.0, 0.0
                               sin(radZ), cos(radZ), 0.0, 0.0
                               0.0, 0.0, 1.0, 0.0
                               0.0,  0.0, 0.0, 1.0);

    return zrot*yrot*xrot*scaling*translation;
}


glm::mat4 Camera::mvp(float l, float r, float b, float t, float n, float f, glm::vec3 eye, glm::vec3 at, glm::vec3 up, glm::mat4 transfomation){
    glm::mat4 view = glm::lookAt(eye, at, up);
    glm::mat4 project = glm::frustrum(l, r, b, t, n, f);
    return project*view*transformation;
}

void Camera::moveX(float x){
    _eye[0] += x;
}

void Camera::moveY(float y){
    _eye[1] += y;
}

void Camera::moveZ(float z){
    _eye[2] += z;
}

void Camera::rotateLR(float lr){
    glm::vec3 at=(_eye[0]+cos(glm::radians(lr)), _eye[1], _eye[2] + sin(glm::radians(lr))); 
    glm::mat4 direction = lookAt(_eye,at,glm::vec3(0.f,1.f,0.f));
    u = glm::vec3(direction[0][0], direction[0][1], direction[0][2]);
    v = glm::vec3(direction[1][0], direction[1][1], direction[1][2]);
    w = glm::vec3(direction[2][0], direction[2][1], direction[2][2]);
}

void Camera::rotateUD(float ud){
    glm::vec3 at=(_eye[0], _eye[1] + sin(glm::radians(ud)), _eye[2] );  
    glm::mat4 direction = lookAt(_eye, at, glm::vec3(0.f,1.f,0.f));
    u = glm::vec3(direction[0][0], direction[0][1], direction[0][2]);
    v = glm::vec3(direction[1][0], direction[1][1], direction[1][2]);
    w = glm::vec3(direction[2][0], direction[2][1], direction[2][2]);
}