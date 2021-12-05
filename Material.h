#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "GLInclude.h"
#include "Lighting.h"
////////////////////////////////////////////////////////////////////////////////
/// @brief Material
////////////////////////////////////////////////////////////////////////////////

//Frankie, Patrick
struct Material {
  glm::vec4 kd;//diffuse
  glm::vec4 ks;//specular
  glm::vec4 ka;//ambient
  float Ns;//shininess

  Material(const glm::vec4& _kd, const glm::vec4& _ks, const glm::vec4& _ka, float _Ns): kd(_kd), ks(_ks), ka(_ka), Ns(_Ns) {}

  // converts strings to float values
  float sTF(const std::string& str) {
     float f = std::stof(str);
     return f;
  }

  void readMtl(const std::string& mtlFile){//read thru one mtl file for each obj
    std::string line;
    std::ifstream mtl;
    mtl.open(mtlFile);

    std::vector<std::string> parsed;

    if(mtl.is_open()){
      while(getline(mtl, line)){

        std::stringstream s(line);
        std::string word;
        while (s >> word) {
            parsed.push_back(word);
        }
        
        if(parsed[0] == "Ka") {
            for (int i = 1; parsed.size(); i++) {
                ka = glm::vec4(sTF(parsed[i+1]),sTF(parsed[i+2]),sTF(parsed[i+3]),sTF(parsed[i+4])); 
            }
            parsed.clear();
        }
        if(parsed[0]=="Kd") {
            for (int i = 1; parsed.size(); i++) {
                kd = glm::vec4(sTF(parsed[i+1]),sTF(parsed[i+2]),sTF(parsed[i+3]),sTF(parsed[i+4]));
            }
            parsed.clear();
        }
        if(parsed[0]=="Ks") {
            for (int i = 1; parsed.size(); i++) {
                ks = glm::vec4(sTF(parsed[i+1]),sTF(parsed[i+2]),sTF(parsed[i+3]),sTF(parsed[i+4]));
            }
            parsed.clear();
        }
        if(parsed[0]=="Ns") {
            Ns = sTF(parsed[1]);
            parsed.clear();
        }
      }
    }

    mtl.close();
  }
  
  

  

glm::vec3 Direction(const glm::vec3& p, const glm::vec3& x)const{
    return glm::normalize(x - p);
}

glm::vec4 lambertian(const Light& L, const glm::vec3& normal, const glm::vec3& x) const{
    glm::vec3 d = L.getPoint(); 
    glm::vec3 l =Direction(x,d);
    //float dist = glm::length(x-d);
    //float a = 1/(L.getLAC()[0] + L.getLAC()[1] * dist + L.getLAC()[2] * dist * dist);//attenuation doesnt work properly
    return kd*L.getId()*std::max(0.f,glm::dot(normal,l));
}

glm::vec4 blinnPhong(const Light& L,const glm::vec3& cam, const glm::vec3& normal, const glm::vec3& x)const{
    glm::vec3 v = glm::normalize(Direction(x, cam));
    glm::vec3 d = L.getPoint();
    glm::vec3 l = glm::normalize(Direction(x,d));//light vector
    //glm::vec3 h= glm::normalize(v+l);
    glm::vec3 r = glm::normalize(glm::reflect(-l, normal));//reflected vector
    //float dist = glm::length(x-d);
    //float a = 1/(L.getLAC()[0] + L.getLAC()[1] * dist + L.getLAC()[2] * dist * dist);//attenuation doesnt work properly
    return ks*L.getIs()*glm::pow(std::max(0.f, glm::dot(v, r)), Ns);
}

glm::vec4 ambientLight(Light L)const{
    return ka*L.getIa();
}

};

#endif
