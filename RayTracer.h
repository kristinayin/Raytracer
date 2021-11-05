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
    RayTracer(int mw, int mh):m_width(mw), m_height(mh){
      m_frame = std::make_unique<glm::vec4[]>(m_width * m_height);
    }
    void clear() const override;
    void render(const Scene& _scene) const override;
    //std::unique_ptr<glm::vec4[]> render(const Scene& s);
    //maybe make some kind of initializer for m_frame

  //private:
    int m_width;
    int m_height;
    std::unique_ptr<glm::vec4[]> m_frame{nullptr}; ///< Framebuffer
};



#endif
