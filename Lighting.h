#ifndef _LIGHTING_H_
#define _LIGHTING_H_

#include "GLInclude.h"
#include <vector>

class Light: public Object{
    //public:
        glm::vec3 point;
        //light intensities for Ambient diffuse & specuar components
        glm::vec3 direction;
        float theta;//cut off angle
        glm::vec3 LAC;//linearattenuation constants
        float attenuation;
        glm::vec3 i_a;
        glm::vec3 i_d;
        glm::vec3 i_s;

        glm::vec3 lambertianShading(glm::vec3 kd, glm::vec3 id, Object o);

        //global ambient light
        Light(const glm::vec3&ia){
            i_a=ia;//only requires one intensity
        }

        //directional
        Light(const glm::vec3& d, const glm::vec3& ia, const glm::vec3& id, const glm::vec3& is){
            direction= d;
            i_a=ia;
            i_d=id;
            i_s=is;
        }
        
        //point light
        Light(const glm::vec3& p, const glm::vec3& ia, const glm::vec3& id, const glm::vec3& is, const glm::vec3& attenconst){
             point = p;
             i_a=ia;
             i_d=id;
             i_s=is;
             LAC = attenconst;
        }
        //spotlight
        Light( const glm::vec3& p, const glm::vec3& d,  const float t, const glm::vec3& ia, const glm::vec3& id, const glm::vec3& is, const glm::vec3& attenconst, const float a){
            point = p;
            direction = d;
            theta = t;
            i_a=ia;
            i_d=id;
            i_s=is;
            LAC = attenconst;
            attenuation = a;//angular attenuation constant
        } 
};

#endif
