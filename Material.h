#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <iostream>

#include "GLInclude.h"
#include "Lighting.h"
////////////////////////////////////////////////////////////////////////////////
/// @brief Material
////////////////////////////////////////////////////////////////////////////////

//Frankie, Patrick
struct Material {

  Material(const glm::vec4& _kd, const glm::vec4& _ks, const glm::vec4& _ka, float _p): kd(_kd), ks(_ks), ka(_ka),p(_p) {}

  glm::vec4 kd;
  glm::vec4 ks;
  glm::vec4 ka;
  float p;

glm::vec3 Direction(const glm::vec3& p, const glm::vec3& x)const{
    return glm::normalize(x - p);
}

glm::vec4 lambertian(const Light& L, const glm::vec3& normal, const glm::vec3& x) const{
    glm::vec3 d = L.getPoint(); 
    glm::vec3 l =Direction(x,d);
    return kd*L.getId()*std::max(0.f,glm::dot(normal,l));
}

glm::vec4 blinnPhong(const Light& L,const glm::vec3& cam, const glm::vec3& normal, const glm::vec3& x)const{
    glm::vec3 v = glm::normalize(Direction(x, cam));
    glm::vec3 d = L.getPoint();
    glm::vec3 l = glm::normalize(Direction(x,d));//light vector
    //glm::vec3 h= glm::normalize(v+l);
    glm::vec3 r = glm::normalize(glm::reflect(-l, normal));//reflected vector
    return ks*L.getIs()*glm::pow(std::max(0.f, glm::dot(v, r)), p);
}

glm::vec4 ambientLight(Light L)const{
    return ka*L.getIa();
}

  glm::vec4 ADSLighting(Light L, const glm::vec3& normal, const glm::vec3& x,const glm::vec3& cam)const{

    glm::vec4 ambient; 
    glm::vec4 diffuse;
    glm::vec4 specular;

    glm::vec3 d = L.getPoint(); 
    glm::vec3 l =Direction(x,d);
    diffuse = kd*L.getId()*std::max(0.f,glm::dot(normal,l));

    glm::vec3 v = Direction(x, cam);
    glm::vec3 h= v+l;
    h=glm::normalize(h);
    specular = ks*L.getIs()*glm::pow(std::max(0.f, glm::dot(v, h)), p);


    ambient = ka*L.getIa();

    return ambient + diffuse + specular;
  }

};

#endif