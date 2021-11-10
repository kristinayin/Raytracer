#ifndef _GL_INCLUDE_H_
#define _GL_INCLUDE_H_

// GL
#define GL_GLEXT_PROTOTYPES
#ifdef OSX
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#else
#include <GL/gl.h>
#endif

// GLFW
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>
// GLM Extensions. In a typical application you should not include all of them,
// but rather just include what you need. GLM_ENABLE_EXPERIMENTAL allows for
// many utilities that have been lightly tested, again this is not necessarily
// recommended.
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>

#endif
