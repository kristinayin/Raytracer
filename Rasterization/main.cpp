////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Contains main function to create a window and run engine that
///        repeatedly generates a framebuffer and displays it.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes

// STL
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

// Engine
#include "GLInclude.h"
#include "CompileShaders.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief Simple vertex class.
struct Vertex {
  glm::vec4 pos; ///< Position
  glm::vec4 col; ///< Color

  Vertex(const glm::vec4& _pos, const glm::vec4& _col) :
    pos{_pos}, col{_col}{}
};

////////////////////////////////////////////////////////////////////////////////
// Global variables - avoid these

// Rendering system
enum class Renderer {RayTracer, Rasterizer};
constexpr Renderer g_renderer = Renderer::Rasterizer;

// Window
int g_width{1360};
int g_height{768};

// RayTracer
GLuint     g_texture; ///< Texture Object
GLuint g_framebuffer; ///< Framebuffer Object
std::unique_ptr<glm::vec4[]> g_frame{nullptr}; ///< Framebuffer

// Rasterizer
GLuint g_program{0}; ///< Shader program
GLuint     g_vao{0}; ///< Vertex Array Object
GLuint     g_vbo{0}; ///< Vertex Buffer Object

// Frame rate
const unsigned int FPS = 60;
float g_frameRate{0.f};
std::chrono::high_resolution_clock::time_point g_frameTime{
  std::chrono::high_resolution_clock::now()};
float g_delay{0.f};
float g_framesPerSecond{0.f};

////////////////////////////////////////////////////////////////////////////////
// Functions

////////////////////////////////////////////////////////////////////////////////
/// @brief Initialize GL settings
void
initialize(GLFWwindow* _window) {
  glClearColor(0.f, 0.f, 0.f, 1.f);

  switch(g_renderer) {
    case Renderer::RayTracer:
      // Generate texture
      glGenTextures(1, &g_texture);

      // Generate framebuffer
      glGenFramebuffers(1, &g_framebuffer);

      g_frame = std::make_unique<glm::vec4[]>(g_width*g_height);

      break;
    case Renderer::Rasterizer:
      glEnable(GL_DEPTH_TEST);

      g_program = compileProgram("Shaders/passthrough.vert",
                                "Shaders/passthrough.frag");

      // Simple static data
      static Vertex vertices[] = {
        Vertex{glm::vec4{-1.f, -1.f, 0, 1}, glm::vec4{1.f, 0.f, 0.f, 1.f}},
        Vertex{glm::vec4{ 1.f,  0.f, 0, 1}, glm::vec4{0.f, 1.f, 0.f, 1.f}},
        Vertex{glm::vec4{ 0.f,  1.f, 0, 1}, glm::vec4{0.f, 0.f, 1.f, 1.f}}
      };

      // Generate vertex array
      glGenVertexArrays(1, &g_vao);
      glBindVertexArray(g_vao);

      // Generate/specify vertex buffer
      glGenBuffers(1, &g_vbo);
      glBindBuffer(GL_ARRAY_BUFFER, g_vbo);
      glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*3, vertices, GL_STATIC_DRAW);

      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,
                            sizeof(Vertex), (char*)NULL + 0);
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE,
                            sizeof(Vertex), (char*)NULL + sizeof(glm::vec4));

      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindVertexArray(0);

      break;
  }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Callback for resize of window
///
/// Responsible for setting window size (viewport) and projection matrix.
void resize(GLFWwindow* window, int _w, int _h) {
  // Resize the framebuffer if we are ray tracing and the screen gets larger.
  if (g_renderer == Renderer::RayTracer && g_width*g_height >= _w*_h) {
    g_frame = std::make_unique<glm::vec4[]>(_w*_h);
  }

  g_width = _w;
  g_height = _h;

  // Viewport
  glfwGetFramebufferSize(window, &g_width, &g_height);
  glViewport(0, 0, g_width, g_height);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Draw function for single frame
void
draw(GLFWwindow* _window, double _currentTime) {
  //////////////////////////////////////////////////////////////////////////////
  // Clear
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if(g_renderer == Renderer::RayTracer) {
    // Not strictly necessary...
    for(int i = 0; i < g_width*g_height; ++i)
      g_frame[i] = glm::vec4(0.f, 0.4f, 0.f, 0.f);
  }

  //////////////////////////////////////////////////////////////////////////////
  // Draw
  switch(g_renderer) {
    case Renderer::RayTracer:
      // Simple static :P
      for(int i = 0; i < g_width*g_height; ++i)
        g_frame[i] = glm::vec4(float(rand())/RAND_MAX, float(rand())/RAND_MAX,
                              float(rand())/RAND_MAX, 1.f);

      // Open GL3 way of copying an image from the CPU to the
      // full screen on the GPU
      glBindTexture(GL_TEXTURE_2D, g_texture);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, g_width, g_height, 0, GL_RGBA,
                  GL_FLOAT, g_frame.get());


      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, g_framebuffer);
      glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, g_texture, 0);

      glBindFramebuffer(GL_READ_FRAMEBUFFER, g_framebuffer);
      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
      glBlitFramebuffer(0, 0, g_width, g_height, 0, 0, g_width, g_height,
                        GL_COLOR_BUFFER_BIT, GL_NEAREST);
      glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
      glBindTexture(GL_TEXTURE_2D, 0);
      break;

    case Renderer::Rasterizer:
      // Render the triangle
      glBindVertexArray(g_vao);
      glDrawArrays(GL_TRIANGLES, 0, 3);
      glBindVertexArray(0);
      break;
  }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Main application loop
void
run(GLFWwindow* _window) {
  using namespace std::chrono;

  std::cout << "Starting main loop" << std::endl;

  while(!glfwWindowShouldClose(_window)) {
    ////////////////////////////////////////////////////////////////////////////
    // Draw
    draw(_window, glfwGetTime());

    ////////////////////////////////////////////////////////////////////////////
    // Show
    glfwSwapBuffers(_window);
    glfwPollEvents();

    ////////////////////////////////////////////////////////////////////////////
    // Record frame time
    high_resolution_clock::time_point time = high_resolution_clock::now();
    g_frameRate = duration_cast<duration<float>>(time - g_frameTime).count();
    g_frameTime = time;
    g_framesPerSecond = 1.f/(g_delay + g_frameRate);
    printf("FPS: %6.2f\n", g_framesPerSecond);

    ////////////////////////////////////////////////////////////////////////////
    // Delay to fix the frame-rate
    g_delay = std::max(0.f, 1.f/FPS - g_frameRate);
    std::this_thread::sleep_for(std::chrono::microseconds(
        static_cast<long int>(g_delay*1000)));
  }

  std::cout << "Ending main loop" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Callback function for keyboard input
/// @param _window
/// @param _key Key
/// @param _scancode Platform specific keycode
/// @param _action Action, e.g., pressed or released
/// @param _mods Keyboard modifiers
void
keyCallback(GLFWwindow* _window, int _key, int _scancode,
           int _action, int _mods) {
  if(_action == GLFW_PRESS) {
    switch(_key) {
      // Escape key : quit application
      case GLFW_KEY_ESCAPE:
        std::cout << "Closing window" << std::endl;
        glfwSetWindowShouldClose(_window, GLFW_TRUE);
        break;
        // Arrow keys
      case GLFW_KEY_LEFT:
      case GLFW_KEY_RIGHT:
        break;
        // Unhandled
      default:
        std::cout << "Unhandled key: " << _key << std::endl;
        break;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Callback function for window closing
/// @param _window
void
windowCloseCallback(GLFWwindow* _window) {
  // Clean up memory by releasing GPU resources
  switch(g_renderer) {
    case Renderer::RayTracer:
      glDeleteTextures(1, &g_texture);
      glDeleteFramebuffers(1, &g_framebuffer);
      break;
    case Renderer::Rasterizer:
      glDeleteBuffers(1, &g_vbo);
      glDeleteVertexArrays(1, &g_vao);
      break;
  }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Error handler
/// @param _code Error code
/// @param _msg Error message
void errorCallback(int _code, const char* _msg) {
  std::cerr << "Error " << _code << ": " << _msg << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
// Main

////////////////////////////////////////////////////////////////////////////////
/// @brief main
/// @param _argc Count of command line arguments
/// @param _argv Command line arguments
/// @return Application success status
int
main(int _argc, char** _argv) {
  //////////////////////////////////////////////////////////////////////////////
  // Initialize
  std::cout << "Initializing GLFWWindow" << std::endl;
  // GLFW
  glfwSetErrorCallback(errorCallback);
  if(!glfwInit()) {
    std::cerr << "GLFW Cannot initialize" << std::endl;
    return 1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(
    g_width, g_height, "Spiderling: A Rudamentary Game Engine", NULL, NULL);
  if(!window) {
    std::cerr << "GLFW Cannot create window" << std::endl;
    return 1;
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  glfwGetFramebufferSize(window, &g_width, &g_height);
  glViewport(0, 0, g_width, g_height);  // Initialize viewport


  // Assign callback functions
  std::cout << "Assigning Callback functions" << std::endl;
  glfwSetFramebufferSizeCallback(window, resize);
  glfwSetKeyCallback(window, keyCallback);
  glfwSetWindowCloseCallback(window, windowCloseCallback);

  // Program initialize
  std::cout << "Initializing application" << std::endl;
  initialize(window);

  //////////////////////////////////////////////////////////////////////////////
  // Main loop
  run(window);

  //////////////////////////////////////////////////////////////////////////////
  // Cleanup GLFW Window
  std::cout << "Destroying GLFWWindow" << std::endl;
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
