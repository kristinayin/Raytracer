#ifndef _RAY_H_
#define _RAY_H_

#include "GLInclude.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief Ray
////////////////////////////////////////////////////////////////////////////////
struct Ray {
  Ray(const glm::vec3 _o,
      const glm::vec3 _d) : 
    m_origin(_o), m_direction(_d) {}

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Get a point along the ray
  /// @param _t Distance along ray
  /// @return Point at @c _t distance along the ray
  glm::vec3 at(float _t) const {
    return m_origin + _t * m_direction;
  }

  glm::vec3    m_origin; ///< Source of ray
  glm::vec3 m_direction; ///< Direction of ray
};

#endif