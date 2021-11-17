#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "GLInclude.h"
#include "Lighting.h"
////////////////////////////////////////////////////////////////////////////////
/// @brief Material
////////////////////////////////////////////////////////////////////////////////

//Frankie
struct Material {

  Material(const glm::vec4& _kd, const glm::vec4& _ks, const glm::vec4& _ka, float _p): kd(_kd), ks(_ks), ka(_ka) {}

  glm::vec4 kd;
  glm::vec4 ks;
  glm::vec4 ka;
  float p;

glm::vec3 Direction(const glm::vec3& p, const glm::vec3& x){
    glm::vec3 n, d, r;
    //numerator
    n= p-x;
    //denominator
    d= p-x;
    //result
    r=d/glm::length(d);
    return r;
}

float Max(float z, float _m){
  if(z<_m){
    return _m;
  }else{
    return z;
  }
}

glm::vec4 lambertian(const Light& L, const glm::vec3& normal, const glm::vec3& x){
    glm::vec3 d = L.getPoint(); 
    glm::vec3 l =Direction(x,d);
    return kd*L.getId()*Max(0.f,glm::dot(normal,l));
}

glm::vec4 blinnPhong(const Light& L, const glm::vec3& cam, const glm::vec3& x){
    glm::vec3 v = Direction(x, cam);
    glm::vec3 d = L.getPoint();
    glm::vec3 l=Direction(x,d);
    glm::vec3 h= v+l;
    h=glm::normalize(h);
    return ks*L.getIs()*glm::pow(Max(0, glm::dot(v, h)), p);
}

glm::vec4 ambientLight(Light L){
    return ka*L.getIa();
}

  glm::vec4 ADSLighting(Light L, const glm::vec3& normal, const glm::vec3& x,const glm::vec3& cam){

    glm::vec4 ambient; 
    glm::vec4 diffuse;
    glm::vec4 specular;

    glm::vec3 d = L.getPoint(); 
    glm::vec3 l =Direction(x,d);
    diffuse = kd*L.getId()*Max(0,glm::dot(normal,l));

    glm::vec3 v = Direction(x, cam);
    glm::vec3 h= v+l;
    h=glm::normalize(h);
    specular = ks*L.getIs()*glm::pow(Max(0, glm::dot(v, h)), p);


    ambient = ka*L.getIa();

    return ambient + diffuse + specular;
  }

  

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