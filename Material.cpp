#include "Material.h"
#include "math.h"
//calculates direction to light from a point x
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

glm::vec4 Material :: lambertian(const Light& L, const glm::vec3& normal, const glm::vec3& x){
    glm::vec3 l = L.getPoint();
    l=Direction(x,l);
    return kd*L.getId()*max(0,dot(n,l));
}

glm::vec4 Material :: blinnPhong(const Light& L, const glm::vec3& cam, const glm::vec3& x){
    glm::vec3 v = Direction(x, cam);
    glm::vec3 l = L.getPoint();
    l=Direction(x,l);
    glm::vec3 h= v+l;
    h=glm::normalize(h);
    return pow(ks*L.getIs()*std::max(0, glm::dot(v, h)), p);
}

glm::vec4 Material :: ambientLight(const Light& L){
    return ka*L.getIa();
}

  glm::vec4 ADSLighting(conat Light& L, const glm::vec3& normal, const glm::vec3& x,const glm::vec3& cam){

      glm::vec4 ambient; 
      glm::vec4 diffuse;
      glm::vec4 specular;

    glm::vec3 l = L.getPoint();
    l=Direction(x,l);
    diffuse = kd*L.getId()*max(0,dot(n,l));

    glm::vec3 v = Direction(x, cam);
    glm::vec3 h= v+l;
    h=glm::normalize(h);
    specular = pow(ks*L.getIs()*std::max(0, glm::dot(v, h)), p);


    ambient = ka*L.getIa();

    return ambient + diffuse + specular;
  }


