#ifndef _PLANE_H_
#define _PLANE_H_

// GL
#include "GLInclude.h"
#include <vector>

//Engine
#include "Collision.h"
#include "Object.h"

class Plane : public Object {
  public:
    Plane() : point(glm::vec3(0,0,0)), normal(normal = glm::vec3(0,0,0)) {}
    
    Plane(float y, glm::vec3 place) : point(place), normal(glm::vec3(0.f, y, 0.f)) {}

    Collision collide(const Ray&_ray) const override;

  private://making this private because its causing an out of scope error?
    glm::vec3 point;//point on the plane
    glm::vec3 normal;//plane's normal
};



#endif