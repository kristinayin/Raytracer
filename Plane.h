#ifndef _PLANE_H_
#define _PLANE_H_

// GL
#include "GLInclude.h"
#include <vector>

//Engine
#include "Collision.h"
#include "Material.h"
#include "Object.h"

class Plane : public Object {
  public:
    
    Plane(const glm::vec3& norm, const glm::vec3& place/*, const Material m*/) : point(place), normal(norm)/*, m_material(m)*/ {}

    Collision collide(const Ray&_ray) const override;

    //Material getMaterial();

    glm::vec3 getNormal();

  private:
    glm::vec3 point, normal;//point on the plane and plane's normal
    Material m_material;//plane material find out how to make this private
};

#endif