#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Collision.h"
#include "Ray.h"
#include "Material.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief Abstract base for all objects
////////////////////////////////////////////////////////////////////////////////
class Object {
  public:
    // Constructors and Destructors
    Object() = default;
    virtual ~Object() = default;
    

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Determine a collision between a ray and the object
    /// @param _ray Ray
    /// @return Collision information
    virtual Collision collide(const Ray& _ray) const = 0;
    //virtual Material getMaterial() const = 0;

    //this function is for model matrix (model -> world transformation)
    glm::mat4 transform(float tx, float ty, float tz, float radX, float radY, float radZ, float sx, float sy, float sz){
      glm::mat4 translation = glm::mat4(1.0, 0.0, 0.0, 0.0,
                                          0.0, 1.0, 0.0, 0.0,
                                          0.0, 0.0, 1.0, 0.0,
                                          tx,  ty,  tz,  1.0);
              
      glm::mat4 scaling = glm::mat4(sx, 0.0, 0.0, 0.0,
                                    0.0, sy, 0.0, 0.0,
                                    0.0, 0.0, sz, 0.0,
                                    0.0,  0.0, 0.0, 1.0);
              
      glm::mat4 xrot = glm::mat4(1.0, 0.0, 0.0, 0.0,
                                0.0, cos(radX), -sin(radX), 0.0,
                                0.0, sin(radX), cos(radX), 0.0,
                                0.0,  0.0, 0.0, 1.0);

      glm::mat4 yrot = glm::mat4(cos(radY), 0.0, sin(radY), 0.0,
                                0.0, 1.0,  0.0, 0.0,
                                -sin(radY), 0.0, cos(radY), 0.0,
                                0.0,  0.0, 0.0, 1.0);

      glm::mat4 zrot = glm::mat4(cos(radZ), -sin(radZ), 0.0, 0.0,
                                sin(radZ), cos(radZ), 0.0, 0.0,
                                0.0, 0.0, 1.0, 0.0,
                                0.0,  0.0, 0.0, 1.0);

      return translation*zrot*yrot*xrot*scaling;
}

};

#endif