#ifndef _LIGHTING_H_
#define _LIGHTING_H_

#include "GLInclude.h"
#include <vector>

class Light: public Object{
    //public:
        glm::vec3 point;
        //light intensities for Ambient diffuse & specuar components
        glm::vec3 intensities;
        glm::vec3 direction;
        float theta;//cut off angle
        glm::vec3 LAC;//linearattenuation constants
        float attenuation;

        //point light
        Light(const glm::vec3& p, const glm::vec3& color, const glm::vec3& attenconst){
             point = p;
             intensities = color;
             LAC = attenconst;
        }
        //spotlight
        Light(const glm::vec3& p, const glm::vec3& color,const glm::vec3& attenconst, glm::vec3 d, float t, float a){
            point = p;
            intensities = color;
            LAC = attenconst;
            direction = d;
            theta = t;
            attenuation = a;



        }
  
};

#endif
