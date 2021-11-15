#ifndef _LIGHTING_H_
#define _LIGHTING_H_

#include "GLInclude.h"

class Light{
    public:
        //glm::vec3 lambertianShading(glm::vec3 kd, glm::vec3 id, Object o);

        //global ambient light
        Light(const glm::vec4&ia): i_a(ia) {}//only requires one intensity

        //directional
        Light(const glm::vec3& d, const glm::vec4& ia, const glm::vec4& id, 
              const glm::vec4& is): direction(d), i_a(ia), i_d(id), i_s(is) {}//linear attenuation always have value of 1
        
        //point light
        Light(const glm::vec3& p, const glm::vec4& ia, const glm::vec4& id, const glm::vec4& is, 
              const glm::vec3& attenconst): point(p), i_a(ia), i_d(id), i_s(is), LAC(attenconst) {}//angluar attenuation always has value of 1


        //spotlight
        Light(const glm::vec3& p, const glm::vec3& d,  const float t, const glm::vec4& ia, 
              const glm::vec4& id, const glm::vec4& is, const glm::vec3& attenconst, 
              const float a): point(p), direction(d), theta(t), i_a(ia), i_d(id), i_s(is), 
              LAC(attenconst), attenuation(a) {}// a is angular attenuation constant

        glm::vec3 getPoint(){
            return point;
        }    
        glm::vec4 getIa(){
            return i_a;
        }  
         glm::vec4 getId(){
            return i_d;
        }
         glm::vec4 getIs(){
            return i_s;
        }  
        glm::vec3 getLAC(){
            return LAC;
        }  


    private:
        glm::vec3 point;
        //light intensities for Ambient diffuse & specuar components
        glm::vec3 direction;
        float theta;//cut off angle
        glm::vec3 LAC;//linearattenuation constants
        float attenuation;
        glm::vec4 i_a;
        glm::vec4 i_d;
        glm::vec4 i_s;

        //glm::vec3 lambertianShading(glm::vec3 kd, glm::vec3 id, Object o);
        //glm::vec3 calculateDirection(const glm::vec3& p, const glm::vec3& x);
        //glm::vec3 lambertianShading(Ray x, Plane o);
        //glm::vec3 blinPhongShading(Ray x, Plane o, Material m, Camera c);
};

#endif
