#include "Sphere.h"

Collision Sphere::collide(const Ray& _ray) const {

  float A = glm::dot(_ray.m_direction, _ray.m_direction);
  float B = glm::dot(2*_ray.m_direction, (_ray.m_origin - m_center));
  float C = glm::dot((_ray.m_origin - m_center), (_ray.m_origin - m_center)) - glm::pow(m_radius, 2.f);

  //both formulas use the discriminant
  float t1 = (-B+glm::sqrt(glm::pow(B, 2.f) - 4*A*C))/(2.f*A);
  float t2 = (-B-glm::sqrt(glm::pow(B, 2.f) - 4*A*C))/(2.f*A);

  glm::vec3 x;//point of collision on sphere
  glm::vec3 n;//normal from collision point on sphere

  if(t1<t2 && t1>0){
    x = _ray.at(t1);
    n = (x - m_center)/m_radius;
    Collision hit1(x, n, &m_material);
    //apply lighting computation here
    return hit1;
  }else if(t2<t1 && t2>0){
    x = _ray.at(t2);
    n = (x - m_center)/m_radius;
    Collision hit2(x, n, &m_material);
    //apply lighting computation here
    return hit2;
  }


  
  return Collision();
  //return hit or miss
}

/*
Material getMaterial(){
  return m_material;
}
*/