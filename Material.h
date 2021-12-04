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
  float p;//shininess
  //update Material struct
  //use ifstream to read in values
  

  // converts strings to float values
  float sTF(const std::string& str) {
     float f = std::stof(str);
     return f;
  }
 
 // parse through, make each word (split by space) into a string
  std::vector<std::string> parse(std::string str){
     std::vector<std::string> split;
     int found;
     while(str.find(" ")!=-1){
       found=str.find(" ");
       split.push_back(str.substr(0,found));
       str=str.substr(found+1);
     }
     split.push_back(str);
     return split;
  }
  
  void readMtl(const std::string& mtlFile){//read thru one mtl file for each obj
    std::string line;
    std::ifstream mtl;
    mtl.open(mtlFile);

    //glm::vec4 getKd;//diffuse
    //glm::vec4 getKs;//specular
    //glm::vec4 getKa;//ambient
    //float getP;

    if(mtl.is_open()){
      while(getline(mtl, line)){
        if(line == "Ka"){//ambient
          ka = glm::vec4(sTF(parsed[1]), sTF(parsed[2]), sTF(parsed[3]), 1);
          
        }else if(line == "Kd"){//diffuse
          kd = glm::vec4(sTF(parsed[1]), sTF(parsed[2]), sTF(parsed[3]), 1);
          
        }else if(line == "Ks"){//specular
          ks = glm::vec4(sTF(parsed[1]), sTF(parsed[2]), sTF(parsed[3]), 1);
          
        }else if(line == "Ns"){//shininess
          p = sTF(parsed[1]);
        }
      }
    }

    mtl.close();
  }
  
  Material(){};
  Material(const glm::vec4& _kd, const glm::vec4& _ks, const glm::vec4& _ka, float _p): kd(_kd), ks(_ks), ka(_ka),p(_p) {}

  

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

};

#endif
