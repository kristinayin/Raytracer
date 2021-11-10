#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include <glm/glm.hpp>

////////////////////////////////////////////////////////////////////////////////
/// @brief One possible storage of vertex information.
////////////////////////////////////////////////////////////////////////////////
struct vertex {

  glm::vec3 m_p; ///< Position
  glm::vec3 m_n; ///< Normal
  glm::vec2 m_t; ///< Texture

  vertex(const glm::vec3& _p, const glm::vec3& _n, const glm::vec2& _t) :
    m_p(_p), m_n(_n), m_t(_t) {}
};

////////////////////////////////////////////////////////////////////////////////
/// @brief One possible mesh data structure
///
/// Vertices will be ordered such that every three form a triangle, e.g.,
/// vertices at indices 0, 1, 2 form a triangle, and then vertices at indices
/// 3, 4, 5 form a triangle, etc.
////////////////////////////////////////////////////////////////////////////////
struct mesh {
  std::vector<vertex> m_vertices;

  mesh(const std::vector<vertex>& _vertices = std::vector<vertex>()) : 
    m_vertices(_vertices) {}
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Parse an obj file into a mesh
/// @param _filename Filename
/// @return Loaded mesh
mesh
parse_obj_file(const std::string& _filename) {
  std::ifstream ifs(_filename);
  if(!ifs) {
    return mesh();
  }
  std::cout << "Parsing: " << _filename << std::endl;

  std::vector<glm::vec3> positions;
  std::vector<glm::vec2> textures;
  std::vector<glm::vec3> normals;
  std::vector<vertex> vertices;

  std::string line;
  while(ifs) {
    getline(ifs, line);

    // Parse here!
  }

  std::cout << "Number of positions: " <<    positions.size() << std::endl;
  std::cout << "Number of  textures: " <<     textures.size() << std::endl;
  std::cout << "Number of   normals: " <<      normals.size() << std::endl;
  std::cout << "Number of     faces: " << (vertices.size()/3) << std::endl;

  return mesh(vertices);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Main driver
/// @param _argc Number of arguments
/// @param _argv Arguments
/// @return Success/failure
int
main(int _argc, char** _argv) {
  if(_argc != 2) {
    std::cerr << "Incorrect usage. Please specify an obj file." << std::endl;
    return 1;
  }

  mesh m = parse_obj_file(_argv[1]);

  if(m.m_vertices.empty()) {
    std::cerr << "Incorrect filename. No information parsed." << std::endl;
    return 1;
  }

  std::cout << "Vertices and Faces final count: " 
    <<   (m.m_vertices.size()) << " vertices and "
    << (m.m_vertices.size()/3) << " faces"
    << std::endl;

  return 0;
}