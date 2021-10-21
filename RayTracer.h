#ifndef _RAYTRACER_H_
#define _RAYTRACER_H_

// GL
#include "GLInclude.h"

// Engine
#include "Renderer.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief Ray tracer
////////////////////////////////////////////////////////////////////////////////
class RayTracer : public Renderer {
  public:

    void clear() const override;
    void render(const Scene& _scene) const override;

  private:
    std::unique_ptr<glm::vec4[]> m_frame{nullptr}; ///< Framebuffer
};

#endif