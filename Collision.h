#ifndef _COLLISION_H_
#define _COLLISION_H_

// GL
#include "GLInclude.h"

// Engine
#include "Material.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief Information of a collision
////////////////////////////////////////////////////////////////////////////////
struct Collision {
  //////////////////////////////////////////////////////////////////////////////
  /// @brief Type of a collision, i.e., hit or miss.
  //////////////////////////////////////////////////////////////////////////////
  enum class Type {
    kMiss = 0, ///< No collision
    kHit       ///< Collision
  };
  
  // Constructors
  Collision() : m_type(Type::kMiss) {}
  Collision(const glm::vec3& _x,
            const glm::vec3& _n,
            const Material*  _m) : 
    m_type(Type::kHit), m_x{_x}, m_normal{_n}, m_material{_m} {}

  Type                m_type; ///< Type of collision object
  glm::vec3              m_x; ///< Point of collision
  glm::vec3         m_normal; ///< Normal at collision
  const Material* m_material; ///< Material of surface
};

/*Collision planeIntersection(Ray i, Plane j){
  if(glm::dot(i._d, j.n)>0){//if vector i dot normal greater than 0
    float t = glm::dot((j.p-i._o), j.n)/glm::dot(i._d, j.n);
    if(t>0){
      Collision result(i._o + t*i._d, plane.n,there needs to be a material here);//result is a ray with the point of collision and the normal of the plane
      kHit = 1;
      return result;
    } 
  }
  return 0;
  //return something else??
}
*/
#endif