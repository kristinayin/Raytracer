#ifndef _RAYTRACER_H_
#define _RAYTRACER_H_

// GL
#include "GLInclude.h"

// Engine
#include "Renderer.h"
//#include <memory>
////////////////////////////////////////////////////////////////////////////////
/// @brief Ray tracer
////////////////////////////////////////////////////////////////////////////////

class RayTracer : public Renderer {
  public:
    void clear() const override;
    void render(const Scene& _scene) const override;
    //maybe make some kind of initializer for m_frame

  private:
    std::unique_ptr<glm::vec4[]> m_frame{nullptr}; ///< Framebuffer
};

#endif