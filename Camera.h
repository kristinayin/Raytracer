#ifndef _CAMERA_H_
#define _CAMERA_H_

// GL
#include "GLInclude.h"

//Patrick (working on camera transformations for Segment 2)
struct Camera{
    glm::vec3 _eye{0, 0, 0}; 
    glm::vec3 u{1, 0, 0}; 
    glm::vec3 v{0, 1, 0}; 
    glm::vec3 w{0, 0, 1};
    float focal = 1;

    //Camera transformation defined by eye, at, and up vectors (view matrix)
    //glm::lookAt(eye, at, up)//this returns a glm::mat4

    //Perspective projection (projecton transformation for perpective view)
    //glm::ortho(l, r, b, t, n, f)
    //glm::frustrum(l, r, b, t, n, f) //this is generalized perspective
    //OR
    //glm::perspective(fovy, aspect, n, f) //this is symmetric perspective
    //fovy is field of view in y direction, theta
    //aspect is aspect ratio, a
    //near and far planes n, f

    //Viewport Transformation (don't remember if we need to include this)
    //glViewport(x, y, width, height)

    //Composing All Matrices Together
    //p' = Mvp * P * V * M * p

    //p is some point on the model??
    //M is model transform (model -> world)
    //V is view/camera transform (world -> camera)
    //P is view's projection matrix (camera -> projection)
    //Mvp is the viewport transform (projection -> screen)

    //need to consider how to transform normal vectors on a sphere

};

/*
class Camera{
    public:
        Camera() {};

        //this function is for model matrix (model -> world transformation)
        glm::mat4 transform(float tx, float ty, float tz, float radX, float radY, float radZ, float sx, float sy, float sz);

        glm::mat4 mvp(float l, float r, float b, float t, float n, float f, glm::vec3 eye, glm::vec3 at, glm::vec3 up, glm::mat4 transfomation);

        void moveZ(float z);//move forward/backward

        void moveX(float x);//move left/right

        void moveY(float y);//move up/down

        void Camera::rotateLR(float lr);//look left right

        void Camera::rotateUD(float ud);//look up down 


    private:
        glm::vec3 _eye;//camera location
        glm::vec3 _at;//where you want the camera to look at
        glm::vec3 _up;//specifies a vector pointing the positive y direction used to create right vector; usually set as glm::vec3(0, 1, 0)
        float n, f;//n is near distance and f is far distance


};

*/

#endif