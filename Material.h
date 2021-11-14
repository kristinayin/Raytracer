#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "GLInclude.h"
#include "Lighting.h"
////////////////////////////////////////////////////////////////////////////////
/// @brief Material
////////////////////////////////////////////////////////////////////////////////
class Material {

  Material(const glm::vec3& _kd, const glm::vec3& _ks, const glm::vec3& _ka): kd(_kd), ks(_ks), ka(_ka) {}

  glm::vec3 kd;
  glm::vec3 ks;
  glm::vec3 ka;

  glm::vec3 Direction(const glm::vec3& p, const glm::vec3& x);

  glm::vec4 lambertian(const Light& L, const glm::vec3& normal, const glm::vec3& x);

  glm::vec4 blinnPhong(const Light& L, const glm::vec3 cam, const glm::vec3& x);

  glm::vec4 ambientLight(const Light& L);

  /*
  glm::vec4 ambient(float xk, float yk, float zk, float xI, float yI, float zI){
    glm::vec4 ka(xk, yk, zk, 0.f);//material for ambient
    glm::vec4 Ia(xI, yI, zI, 0.f);//intensity to ambient
    glm::vec4 ambientAns = ka*Ia;//ambient light eqn
    return ambientAns;

  }

  glm::vec4 diffuse(float xk, float yk, float zk, float xI, float yI, float zI){
    glm::vec4 kd(xk, yk, zk, 0.f);//material for diffuse
    glm::vec4 Id(xI, yI, zI, 0.f);//intensity for diffuse
    glm::vec3 n(0.f, 0.f, 0.f);//normal
    glm::vec4 nNew = glm::vec4(n, 0.f);//convert to vector 4
    glm::vec3 l(0.f, 0.f, 0.f);//light vector??
    glm::vec4 lNew = glm::vec4(l, 0.f);//convert to vector 4
    glm::vec4 diffuseAns = kd*Id*glm::max(0.f, glm::dot(nNew, lNew));//diffuse lighting eqn
    return diffuseAns;
  }

  glm::vec4 specular(float xk, float yk, float zk, float xI, float yI, float zI, float p){
    //p is shininess value
    glm::vec4 ks(xk, yk, zk, 0.f);//material for specular
    glm::vec4 Is(xI, yI, zI, 0.f);//intensity for specular
    glm::vec3 v(0.f, 0.f, 0.f);//direction of camera
    glm::vec4 vNew = glm::vec4(v, 0.f);//converted to vec4
    glm::vec3 l(0.f, 0.f, 0.f);//light vector??
    glm::vec3 length(v+l);//magnitude of v+l
    glm::vec3 h = (v+l)/length;//This has an out of scope error is l supposed to be light?
    glm::vec4 hNew = glm::vec4(h, 0.f);//converted to vec4
    glm::vec4 specularAns = ks*Is*(glm::pow(glm::max(0.f, glm::dot(vNew, hNew)), p));//specular lighting eqn
    return specularAns;
  }*/
};

#endif