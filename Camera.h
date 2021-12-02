#ifndef _CAMERA_H_
#define _CAMERA_H_

// GL
#include "GLInclude.h"

//Patrick (working on camera transformations for Segment 2)
/*
class Camera{
    public:
        Camera(glm::vec3 eye, glm::vec3 at, glm::vec3 up, float n, float f): _eye(eye), _at(at), _up(up), _n(n), _f(f) {};

        Camera(): _eye(glm::vec3{0, 0, 0}), _at(glm::vec3 {0, 0, 1}), _up(glm::vec3 {0,1,0}), _n(1), _f(10){};
        //this function is for model matrix (model -> world transformation)
        //glm::mat4 transform(float tx, float ty, float tz, float radX, float radY, float radZ, float sx, float sy, float sz);

        glm::mat4 view(glm::vec3 eye, glm::vec3 at, glm::vec3 up){
            return glm::lookAt(eye, at, up);
        }

        void moveZ(float z);//move forward/backward

        void moveX(float x);//move left/right

        void moveY(float y);//move up/down

        void rotateLR(float lr);//look left right

        void rotateUD(float ud);//look up down

        int getN() const{
            return _n;
        }

        const glm::vec3& getEye() const{
            return _eye;
        }

        //need to include a point when doing mv matrix
        //camera uses view matrix
        //object uses transformation matrix

        //add a bunch of getter functions

        /*
        glm::vec3 _eye{0, 0, 0}; 
        glm::vec3 u{1, 0, 0}; 
        glm::vec3 v{0, 1, 0}; 
        glm::vec3 w{0, 0, 1};
        float focal = 1;
        

    private:
        glm::vec3 _eye;//camera location
        glm::vec3 _at;//where you want the camera to look at
        glm::vec3 _up;//specifies a vector pointing the positive y direction used to create right vector; usually set as glm::vec3(0, 1, 0)
        float _n, _f;//n is near distance and f is far distance

        //camera coor
        /*
        glm::vec3 u;
        glm::vec3 x;
        glm::vec3 w;
        

};
*/

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





#endif