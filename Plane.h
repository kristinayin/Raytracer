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
    Plane(float y, const glm::vec3& place) : point(place), normal(0, y, 0) {}

    Collision collide(const Ray&_ray) const override;

  private://making this private because its causing an out of scope error?
    glm::vec3 point, normal;//point on the plane and plane's normal
    Material m_material;//plane material
};

#endif