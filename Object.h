#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Collision.h"
#include "Ray.h"

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
};

#endif