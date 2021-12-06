/*
 External resource: https://learnopengl.com/Getting-started/Camera
 */

#ifndef _CAMERA_H_
#define _CAMERA_H_

// GL
#include "GLInclude.h"

//Patrick (working on camera transformations for Segment 2)


class Camera{
    public:
        Camera(glm::vec3 eye, glm::vec3 at, glm::vec3 up, float focal, float fov, float ratio): _eye(eye), _at(at), _up(up), _focal(focal), _fov(fov), _ratio(ratio){
            _t = focal*tan(glm::radians(fov/2));
            _b = -_t;
            _r = ratio*_t;
            _l = -_r;
        };

        Camera(): _eye(glm::vec3{0, 0, 0}), _at(glm::vec3 {0, 0, 1}), _up(glm::vec3 {0,1,0}), _focal(1){};

        glm::mat4 view(glm::vec3 eye, glm::vec3 at, glm::vec3 up){
            return glm::lookAt(eye, at, up);
        }

        void moveZ(float z);//move forward/backward

        void moveX(float x);//move left/right

        void moveY(float y);//move up/down

        void rotateLR(float lr);//look left right

        void rotateUD(float ud);//look up down

        float getFocal() const{
            return _focal;
        }

        float getTop() const{
            return _t;
        }

        float getBott() const{
            return _b;
        }

        float getLeft() const{
            return _l;
        }

        float getRight() const{
            return _r;
        }

        const glm::vec3& getEye() const{
            return _eye;
        }

        

    private:
        glm::vec3 _eye;//camera location
        glm::vec3 _at;//where you want the camera to look at
        glm::vec3 _up;//specifies a vector pointing the positive y direction used to create right vector; usually set as glm::vec3(0, 1, 0)
        float _focal, _t, _b, _l, _r;
        float _fov;//camera's field of view angle in the y direction
        float _ratio;//aspect ratio for the camera

};

#endif
